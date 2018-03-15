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

ISR (TIMER0_OVF_vect)
{
	PORTB = ~ PORTB;
	TIFR0 |= (1 <<TOV0);
}

int main(void)
{
	int count = 60;
	DDRB |= (1<<5);
	PORTB &= ~(1<<5);

	TCCR0A |= (1 << CS01) | (1<<CS00);
	TIMSK0 = (1 <<TOIE0);
	sei();
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {

    }
}

