/*
 * DA4_Ser.c
 *
 * Created: 4/15/2018 3:14:20 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000L
#define SER_MIN 97
#define SER_MAX 535

void initatePWM();					//initate PWM
void ADCinit();						//Initiate ADC
float SER_position(unsigned short);	//Get Servo position


int main(void)
{
	unsigned short val;			//hold the value from ADC
	float servo;				//hold the servo position

	ADCinit();
	initatePWM();

    while (1) 
    {
		ADCSRA |= (1<<ADSC);		//start ADC Conversion
		//wait for conversion
		while((ADCSRA & (1<<ADIF)) == 0);

		if(!(val == (ADCH<<1)))
		{
			val = ADCH<<1;	//take the value from the upper bits of ADC
		}

		servo = SER_position(val);//get voltage
		servo = (servo * 438)+97; //get positon

		//OCR1A gets the value from servo
		if(servo < SER_MIN)
			OCR1A = SER_MIN;
		else
			OCR1A = (int)servo;
    }
}

void initatePWM()
{
	ICR1 = 4999;

	TCCR1A = (1<<COM1A1)|(1<<WGM11);		//set Timer 1 to top of TCR1, FAST PWM
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);		//
}

void ADCinit()
{
	//SET ADC0 as an input
	DDRC |= (0<<PC0);

	//PWM pin (OC1A)
	DDRB |= (1<<PB1);
	
	//SET AVcc with external capacitor at AREF
	ADMUX = 0x60;
	
	//Turn on the ADC for conversion
	ADCSRA = 0x87;

	//Run in Free mode
	ADCSRB = 0x00;
}

float SER_position(unsigned short val)
{
	return ((val*5)/1024.0);
}