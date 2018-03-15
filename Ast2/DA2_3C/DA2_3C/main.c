/*
 * DA2_3C.c
 *
 * Created: 3/14/2018 8:39:47 PM
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int count = 0;
	DDRB |= (1<<5);
	PORTB &= ~(1<<5);

    /* Replace with your application code */
    while (1) 
    {
		OCR0A = 255;
		TCCR0A |= (1<<WGM01);
		TCCR0B |= (1<<CS00);
		while((TIFR0 &(1<<OCF0A)) == 0);
		count++;
		TIFR0 = 0x02;
		if(count > 250)
		{
			PORTB = ~PORTB;
		}
	}
}

