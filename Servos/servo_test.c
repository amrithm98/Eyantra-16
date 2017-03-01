#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void port_init()
{
	DDRB= DDRB | 0x20;
	PORTB = PORTB | 0x20;
	DDRB = DDRB | 0x40;
	PORTB = PORTB | 0x40;
	DDRB = DDRB | 0x80;
	PORTB = PORTB | 0x80;
} 
void timer1_init()
{
	TCCR1A = 0x00;
	ICR1 = 1023;
	TCNT1H = 0xFC;
	TCNT1L = 0x01;
	OCR1A = 1023;
	OCR1B = 1023;
	OCR1C = 1023;
	TCCR1A = 0xAB;
	TCCR1B = 0x0C;
}
// void servo_1_rot(unsigned char degrees)
// {
// 	float regval = ((float)degrees*0.512)+34.56;
// 	OCR1A = (uint16_t)regval;
// }
void servo_1(unsigned char degrees)  
{
 float PositionPanServo = 0;
  PositionPanServo = ((float)degrees / 1.86) + 35.0;
 OCR1AH = 0x00;
 OCR1AL = (unsigned char) PositionPanServo;
}
void servo_2(unsigned char degrees)
{
 float PositionTiltServo = 0;
 PositionTiltServo = ((float)degrees / 1.86) + 35.0;
 OCR1BH = 0x00;
 OCR1BL = (unsigned char) PositionTiltServo;
}
void servo_1_free(void)
{
	OCR1C = 1023;
}
void init()
{
	cli();
	port_init();
	timer1_init();
	sei();
}
int main(void)
{
	init();
	while(1){
	servo_1(0);
	_delay_ms(1000);
	servo_1(90);
	_delay_ms(1000);
	}

}
