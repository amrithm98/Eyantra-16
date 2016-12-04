// Amrith M ... 4/12/16	...White Line Follower FB5
#define F_CPU 14745600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.c"

#define THRESHOLD 50		//Designing White Line Follower

#define MAX_VEL 255

#define MIN_VEL 150

unsigned char ADC_Conversion(unsigned char);

unsigned char ADC_Value;

unsigned int value;

unsigned char Left_white_line = 0;

unsigned char Center_white_line = 0;

unsigned char Right_white_line = 0;

void motion_pin_config(void)
{
	DDRA= DDRA | 0x0F; //0000 1111 --->	PA3 PA2 PA1 PA0 (HIGH)
	DDRL= DDRL | 0x18; //0001 1000 ---> PL3 PL4 (HIGH)
	PORTA= PORTA & 0xF0;
	PORTL= PORTL | 0x18;
}

void init_timer5(void)	//Timer For PWM
{
	TCCR5B = 0x00;	//stop
	TCNT5H = 0xFF;	//counter higher 8 bit value to which OCRxH is compared with
	TCNT5L = 0x01;	//counter higher 8 bit value to which OCRxH is compared with
	OCR5AH = 0x00;	//Output compare register high for left motor
	OCR5AL = 0xFF;	//Output compare register low for left motor
	OCR5BH = 0x00;	//Output compare register high for right motor	
	OCR5BL = 0xFF;	//Output compare register high for right motor
	OCR5C  = 0xFF;	//Motor C1
	OCR5CH = 0x00;	//Motor C1
	OCR5CL = 0xFF;
	TCCR5A = 0xA9;

/* COM5A1=1,COM5A0=0,COM5B1=1,COM5B0=0,COM5C1=1,COM5C0=0
For Overriding normal port functionality to OCRnA ouputs
WGM51=0,WGM50=1 along with WGM52 in TCCRB for selecting fast PWM 8 bit mode
*/

	TCCR5B = 0x0B;	//WGM12=1,CS12=0,CS11=1,CS10=1	(Prescaler=64)

}

void velocity(unsigned char left,unsigned char right)	//Set PWM Velocity
{
	OCR5AL = (unsigned char) left;
	OCR5BL = (unsigned char) right;
}

void motion_set(unsigned char dir)
{
	unsigned char PortA_Restore=0;
	dir &= 0x0F;			//Remove Upper nibbel
	PortA_Restore= PORTA;	//Setting PortA_Restore to current PORTA status			
	PortA_Restore &= 0xF0;	//Setting lower nibbel to 0 
	PortA_Restore |=dir;	//Setting PortA_Restore to current dir
	PORTA=PortA_Restore;	//Setting the current status of PORTA
}

//MOTION			  // RB  RF  LF  LB						
void forward(void)    // PA3 PA2 PA1 PA0
{
	motion_set(0x06);   // 0 1 1 0
}

void backward(void)
{
	motion_set(0x09);	// 1 0 0 1
}

void stop(void)
{
	motion_set(0x00);
}

void lcd_port_config (void)
{
 DDRC = DDRC | 0xF7;    //all the LCD pin's direction set as output
 PORTC = PORTC & 0x80;  // all the LCD pins are set to logic 0 except PORTC 7
}

void adc_pin_config(void)
{
	DDRF=0x00;
	PORTF=0x00;
	DDRK=0x00;
	PORTK=0x00;
}

void adc_init(void)
{
	ADCSRA=0x00;
	ADCSRB=0x00;
	ADMUX=0x00;
	ADCSRA=0x86;	//ADEN=1 ADIE=1....
	ACSR=0x80;
}

void init_devices(void)
{
	cli();
	motion_pin_config();
	init_timer5();
	lcd_port_config();
	adc_pin_config();
	adc_init();
	sei();
}

unsigned char ADC_Conversion(unsigned char ch)
{
	unsigned char a;
	if(ch>7)
	{
		ADCSRB=0x08;
	}
	ch=ch & 0x07;
	ADMUX=0x20 | ch;
	ADCSRA =ADCSRA | 0x40;		//set start conv bit
	while((ADCSRA & 0x10)==0);	//wait for adc conv to complete
	a=ADCH;						//Result stored here after convo
	ADCSRA=ADCSRA | 0x10;		//Clear ADIF by setting it to 1
	ADCSRB=0x00;
	return a;
}

void print_sensor(char row,char col,unsigned char channel)
{
	ADC_Value=ADC_Conversion(channel);
	lcd_print(row,col,ADC_Value,3);
}

int main(void)
{
	unsigned char flag =0;
	init_devices();
	lcd_set_4bit();
	lcd_init();
	velocity(MAX_VEL,MAX_VEL);    // Set the speed to max velocity
 	lcd_print(2,1,MAX_VEL,3);
 	lcd_print(2,5,MAX_VEL,3);
	forward(); 
	while(1)
	{
		Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
		Center_white_line = ADC_Conversion(4);	//Getting data of Center WL Sensor
		Right_white_line = ADC_Conversion(5); //Getting data of Right WL Sensor
		print_sensor(1,1,1);
		print_sensor(1,5,2);
		print_sensor(1,9,3);
		flag=0;

		if(Center_white_line<THRESHOLD)              // Is middle Whiteline is within threshold limit
		{                                             
			flag=1;
			velocity(MAX_VEL,MAX_VEL);      // Run robot at max velocity 
			lcd_print (2,1,MAX_VEL,3);
			lcd_print (2,5,MAX_VEL,3);
		}
		//Right Turn
		if((Left_white_line>THRESHOLD) && (flag==0))  // Is left Whiteline is not within threshold limit
		{                                             
			flag=1;                                                       
			velocity(MAX_VEL,MIN_VEL);      // Run robot left wheel at max velocity and right wheel 
			lcd_print (2,1,MAX_VEL,3);           // at min velocity
			lcd_print (2,5,MIN_VEL,3);
		}
		//Left Turn
		if((Right_white_line>THRESHOLD) && (flag==0)) // Is right Whiteline is not within threshold limit
		{
			flag=1;
			velocity(MIN_VEL,MAX_VEL);      // Run robot right wheel at max velocity and left wheel 
			lcd_print (2,1,MIN_VEL,3);           // at min velocity
			lcd_print (2,5,MAX_VEL,3);
		}
		//Out of Track
		if(Center_white_line>THRESHOLD && (Left_white_line-50)>THRESHOLD && Right_white_line>THRESHOLD && (flag == 0))
	                                // if all Whiteline sensor are not within threshold limit    
		{
			flag=1;
			velocity(0,0);      // stop the robot
			lcd_print (2,1,0,3);
			lcd_print (2,5,0,3);
		}

	}
}
