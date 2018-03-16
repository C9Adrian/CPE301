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
	DDRB = 0xff;			//set portb to output
	PORTB = 0x00;			//set portb to low
	DDRD = 0x00;			//set portd to inputs
	PORTD = 0xFF;			//set portd to high

	PORTB = 0;
    /* Replace with your application code */
    while (1) 
    {
		if(~PIND & (1<<PD0))		//if button is pushed
		{
			_delay_ms(1000);		//delay 1 second
			PORTB &= ~(1<<5);		//turn on
			_delay_ms(1000);		//delay 1 second
			PORTB |= (1<<5);		//turn off
		}
		else
		{
			PORTB = PORTB &~ (1<<5);	//else its always off
		}

    }
}

