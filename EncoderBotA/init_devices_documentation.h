void init_devices() {
	// Clears the global interrupt
	cli();
	// Initialization : Initializing all the devices connected to the ports and other pins
	// robot motion pins config
	// Logic: Initialization : Function to configure ports to enable robot's motion (Port A and Port L here where the motors are connected and where pwm is generated)
	DDRA = DDRA | 0x0F;
	PORTA = PORTA & 0xF0;
	DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
	PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM.
	// left encoder pin config
	// Function to configure INT4 (PORTE 4) pin as input for the left position encoder
	DDRE  = DDRE & 0xEF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x10; //Enable internal pull-up for PORTE 4 pin
	// right encoder pin config
	// Function to configure INT5 (PORTE 5) pin as input for the right position encoder
	DDRE  = DDRE & 0xDF;  //Set the direction of the PORTE 4 pin as input
	PORTE = PORTE | 0x20; //Enable internal pull-up for PORTE 4 pin
	// Buzzer Pin
	// Initialization : Function to configure ports to use buzzer pin
	DDRC=DDRC | 0x08; 		// Port C pin 3 as output
	PORTC=PORTC & 0xF7;
	// Configuring the LCD Pins to function
	DDRC = DDRC | 0xF7;    //all the LCD pin's direction set as output
	PORTC = PORTC & 0x80;  // all the LCD pins are set to logic 0 except PORTC 7
	// Initialization : Function to configure ports for adc conversion. Ports where sensors are attached are configured for adc conversion.
	DDRF=0x00;
	PORTF=0x00;
	DDRK=0x00;
	PORTK=0x00;
	// Configuring the timer5 registers in Atmega2560 for using PWM functionalities
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
	// Initializing the interrput pins where left encoder is connected
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x02; // INT4 is set to trigger with falling edge
	EIMSK = EIMSK | 0x10; // Enable Interrupt INT4 for left position encoder
	sei();   // Enables the global interrupt 
	// Initializing the interrput pins where right encoder is connected
	cli(); //Clears the global interrupt
	EICRB = EICRB | 0x08; // INT5 is set to trigger with falling edge
	EIMSK = EIMSK | 0x20; // Enable Interrupt INT5 for right position encoder
	sei();   // Enables the global interrupt
	// Initialization : Initializing Registers for ADC Conversion
	ADCSRA=0x00;
	ADCSRB=0x00;
	ADMUX=0x00;
	ADCSRA=0x86;	//ADEN=1 ADIE=1....
	ACSR=0x80;
	sei();   // Enables the global interrupt
}