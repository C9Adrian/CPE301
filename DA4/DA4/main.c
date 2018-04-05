/*
 * DA4.c
 *
 * Created: 4/4/2018 9:26:15 PM
 * Author : Luis
 */  

#ifndef F_CPU
#define F_CPU 16000000
#endif

#define BAUD 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUD *16UL)))-1)

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "ioe.h"

void adc_init();

volatile unsigned int adc_temp;
volatile unsigned int tempFar;
volatile char RecievedChar;
char outs[20];
int main(void)
{
    /* Replace with your application code */
	//adc_init();
	//USART_init();
	usart0_init_();					//initialize usart
	adc_init();						//initialize adc
	
	DDRC = 0b00000000;
	while(1){
			_delay_ms(1000);
	}
}

void adc_init()
{
	ADMUX =0;
	ADCSRA= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);	//sample rate of 125kHz at 16MHz
	ADMUX |= (1<<REFS0);							//Set ADC reference to AVCC
	ADMUX |= (1<<ADLAR);							//Left adjust ADC Result to allow 8 bit reading
	
	ADCSRA |= (1<<ADIE);							//set ADC to intruppt mode
	ADCSRA |= (1<<ADEN);							//Enable ADC
	ADCSRA |= (1<<ADATE);							//set ADC auto trigger enable
	ADCSRB = 0;										//0 for free running mode
	ADCSRA |= (1<<ADSC)	;							//start A2D Conversions
	
	sei();
	
}

ISR(ADC_vect)
{
	adc_temp = ADCH;					//grab voltage
	adc_temp = (5*adc_temp*100/1024);	//calculate temperature from voltage in celuis
	tempFar = adc_temp * (1.8);
	tempFar = tempFar +32;			//convert to far.
	//printm("Temperature = ");
	print_int(adc_temp);				//print the value
	printm(" ");
	print_int(tempFar);
	printm("\n");			
	_delay_ms(1000);					//delay
}

