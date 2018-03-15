/*
 * DA2_5C.c
 *
 * Created: 3/15/2018 11:51:55 AM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 1<<5;		//;set pinb5 to output
	PORTB = 0x00;		//;set portb to low
	PORTD = 1 <<2;		//;set pind2 to input
	PORTD = 0xff;		//;set it to high by default
	EIMSK = (1 <<INT0);	//enable pin interrupt
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

ISR (INT0_vect)
{
	_delay_ms(10000);		//delay for a second
	PORTB = ~PORTB;			//turn on LED
	_delay_ms(10000);		//wait for a second
	PORTB = ~PORTB;			//turn off LED
	EIFR |= (1 << INTF0);	//Clear flag
}
