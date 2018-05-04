/*
 * DA4_Step.c
 *
 * Author : Adrian
 */ 

#include <avr/io.h>
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

void adc_init(void);

volatile int adc_delay;

int main(void)
{
	DDRB = 0xFF; //Port B as output
    /* Replace with your application code */
    while (1) 
    {
		while(ADCSRA & (1<<ADSC)) {}
		adc_delay = ADC;

		adc_delay = adc_delay * 100; //setting the delay
		
		//i couldnt figure out how to use CTC mode to control stepper motor
		PORTB = 0x66;
		_delay_ms(adc_delay);
		PORTB = 0xCC;
		_delay_ms(adc_delay);
		PORTB = 0x99;
		_delay_ms(adc_delay);
		PORTB = 0x33;
		_delay_ms(adc_delay);
    }
}

//init the adc
void adc_init()
{
	ADMUX =0;
	ADCSRA= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);	//sample rate of 125kHz at 16MHz
	ADMUX |= (1<<REFS0);							//Set ADC reference to AVCC
	ADMUX |= (1<<ADLAR);							//Left adjust ADC Result to allow 8 bit reading
	
	ADCSRA |= (1<<ADEN);							//Enable ADC
	ADCSRA |= (1<<ADATE);							//set ADC auto trigger enable
	ADCSRB = 0;										//0 for free running mode
	ADCSRA |= (1<<ADSC)	;							//start A2D Conversion
	
}