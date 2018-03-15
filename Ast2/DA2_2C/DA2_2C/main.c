/*
 * DA2_2C.c
 *
 * Created: 3/14/2018 8:06:49 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	PORTB = 0x00;
	DDRD = 0x00;
	PORTD = 0xFF;

	PORTB = 0;
    /* Replace with your application code */
    while (1) 
    {
		if(~PIND & (1<<PD0))
		{
			_delay_ms(1000);
			PORTB &= ~(1<<5);
			_delay_ms(1000);
			PORTB |= (1<<5);
		}
		else
		{
			PORTB = PORTB &~ (1<<5);
		}

    }
}

