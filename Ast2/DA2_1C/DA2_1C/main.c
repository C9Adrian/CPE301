/*
 * DA2_1C.c
 *
 * Created: 3/6/2018 5:23:33 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0x00;
	DDRB |=(1<<PB5);

    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(1000);
		PORTB &= ~(1<<PB5);
		_delay_ms(1000);
		PORTB |= (1<<PB5);
    }
}

