/*
 * DA2_4C.c
 *
 * Created: 3/15/2018 11:18:25 AM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED PD5

ISR (TIMER0_OVF_vect)		//OVR ISR
{
	PORTB = ~ PORTB;		//TOGGLE the PORTB
	TIFR0 |= (1 <<TOV0);	//Clear flag
}

int main(void)
{
	int count = 60;	 		//set count equal to 60
	DDRB |= (1<<5);			//set pinb5 to output
	PORTB &= ~(1<<5);		//set pinb5 to low

	TCCR0A |= (1 << CS01) | (1<<CS00);	//prescalar 1024 timer0 noraml mode
	TIMSK0 = (1 <<TOIE0);				//enable timer0 interrupt
	sei();
	
    /* Replace with your application code */
    while (1) 
    {

    }
}

