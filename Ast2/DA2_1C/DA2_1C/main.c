/*
 * DA2_1C.c
 *
 * Created: 3/6/2018 5:23:33 PM
 * Author : Adrian
 */ 

//C code of DA2_1
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0x00;		
	DDRB |=(1<<PB5);		//set pinb 5 to output

    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(10000);		//delay 1 second
		PORTB &= ~(1<<PB5);		//toggle LED
		_delay_ms(10000);		//delay 1 second
		PORTB |= (1<<PB5);		//toogle LED
    }
}

