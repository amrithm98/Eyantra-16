/*
* Function Name:	ADC_Conversion
* Input:			ch(character storing the channel for ADC Conversion)
* Output:			Digital Sensor Readings
* Logic:			Converting the analog Readings to Digital values
* Example Call:		ADC_Conversion(3)
*/

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

/*
* Function Name:	print_sensor(char row,char col,unsigned char channel)
* Input:			row,col,channel(characers denoting row,col,ADC Channel to print on LCD)
* Output:			prints the output on LCD
* Logic:			Converting the analog Readings to Digital values and printing them on LCD
* Example Call:		print_sensor(1,1,3);
*/

void print_sensor(char row,char col,unsigned char channel)
{
	ADC_Value=ADC_Conversion(channel);
	lcd_print(row,col,ADC_Value,3);
}