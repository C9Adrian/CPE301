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
	int count = 0;			//variable to check overflow
	DDRB |= (1<<5);			//set pinb5 to output and to low
	PORTB &= ~(1<<5);

    /* Replace with your application code */
    while (1) 	
    {
		OCR0A = 255;						//maxium value for OCR0A
		TCCR0A |= (1<<WGM01);				//Put TIMER0 into CTC MODE
		TCCR0B |= (1<<CS00);
		while((TIFR0 &(1<<OCF0A)) == 0);	//Wait for flag to be cleared
		count++;							//inc count
		TIFR0 = 0x02;						//Clear flag
		if(count > 250)						//if count is count greater than				
		{									//250 
			PORTB = ~PORTB;					//toggle LED
		}
	}
}

