void initBotDevices() {
	cli();
	DDRA = DDRA | 0x0F;
	PORTA = PORTA & 0xF0;
	DDRL = DDRL | 0x18;
	PORTL = PORTL | 0x18;
	DDRE  = DDRE & 0xEF;
	PORTE = PORTE | 0x10;
	DDRE  = DDRE & 0xDF;
	PORTE = PORTE | 0x20;
	DDRC=DDRC | 0x08;
	PORTC=PORTC & 0xF7;
	DDRC = DDRC | 0xF7;
	PORTC = PORTC & 0x80;
	DDRF=0x00;
	PORTF=0x00;
	DDRK=0x00;
	PORTK=0x00;
	TCCR5B = 0x00;
	TCNT5H = 0xFF;
	TCNT5L = 0x01;
	OCR5AH = 0x00;
	OCR5AL = 0xFF;
	OCR5BH = 0x00;
	OCR5BL = 0xFF;
	OCR5C  = 0xFF;
	OCR5CH = 0x00;
	OCR5CL = 0xFF;
	TCCR5A = 0xA9;
	TCCR5B = 0x0B;
	cli();
	EICRB = EICRB | 0x02;
	EIMSK = EIMSK | 0x10;
	sei();
	cli();
	EICRB = EICRB | 0x08;
	EIMSK = EIMSK | 0x20;
	sei();
	ADCSRA=0x00;
	ADCSRB=0x00;
	ADMUX=0x00;
	ADCSRA=0x86;
	ACSR=0x80;
	sei();
}

// BUZZER OPERATIONS: pin 3 to high/low 0000 1000 / 0000 0000

void buzzerOn() { PORTC = 0x08; }
void buzzerOff() { PORTC = 0x00; }

// MOTION OPERATIONS

/*
* Function Name:	motionSet
* Input:			Direction - (character-Hexadecimal equivalent of the motor port configuration)
* Output:			Initialize the required registers
* Logic :			Function used for setting motor's direction. Robot will start moving in the specified direction once motionSet is called
* Example Call:		motionSet(0x00)
*/

void motionSet (unsigned char Direction) {
	unsigned char PortARestore = 0;
	Direction &= 0x0F; 		// removing upper nibbel for the protection
	PortARestore = PORTA; 		// reading the PORTA original status
	PortARestore &= 0xF0; 		// making lower direction nibbel to 0
	PortARestore |= Direction; // adding lower nibbel for forward command and restoring the PORTA status
	PORTA = PortARestore; 		// executing the command
}

void moveForward() { motionSet(0x06); } // both wheels forward
void moveBackward() { motionSet(0x09); } // both wheels backward
void moveLeft() { motionSet(0x05); } // left wheel backward and right wheel forward
void moveRight() { motionSet(0x0A); } // right wheel backward and left wheel forward
void moveLeftSoft() { motionSet(0x04); } // left wheel stop and right wheel forward
void moveRightSoft() { motionSet(0x02); } // right wheel stop and left wheel forward
void stop() { motionSet(0x00); } // stop both wheels
void velocityChange (unsigned char left, unsigned char right) { OCR5AL = (unsigned char) left; OCR5BL = (unsigned char) right; } // Set PWM Velocity
void rotateAngles(int degrees) {
	float ReqdShaftCount = 0;
	unsigned long int ReqdShaftCountInt = 0;
	if (degrees >= 0) {
		moveRight();
	} else {
		moveLeft();
		degrees = -degrees;
	}
	ReqdShaftCount = (float) Degrees/ 4.090; // division by resolution to get shaft count
	ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
	ShaftCountLeft = ShaftCountRight = 0;
	while ((ShaftCountRight >= ReqdShaftCountInt) && (ShaftCountLeft >= ReqdShaftCountInt));
}

// ENCODER OPERATIONS

ISR(INT5_vect) { ShaftCountLeft++; }
ISR(INT4_vect) { ShaftCountRight++; }

// SENSOR

/*
* Function Name:	Sharp_dist
* Input:			ADC Reading of front IR Sharp Sensor
* Output:			Distance in mm of Sharp sensor from the nearest detected obstacle
* Logic :			Calculating distance from volatage value of the sensor using the formula in sensor datasheet
* Example Call:		Sharp_dist(20)
*/

unsigned int Sharp_dist(unsigned char adc_reading)
{
	float distance;
	unsigned int distanceInt;
	distance = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
	distanceInt = (int)distance;
	if(distanceInt>800)
	{
		distanceInt=800;
	}
	return distanceInt;
}