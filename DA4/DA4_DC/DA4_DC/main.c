/*
 * DA4_DC.c
 *
 * Created: 4/15/2018 2:33:02 PM
 * Author : Adrian	
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

unsigned short readADC();			//read value from the adc
void initatePWM();					//set PWM
void ADCinit();						//initalize ADC
void updateDC(unsigned char);					//update DC

int main(void)
{
	unsigned short val;				//this holds the value read from the ADC
	unsigned char DC;				//the duty cycle

	DDRD = 0x0F;					//set the nibble as output

	ADCinit();
	initatePWM();

    /* Replace with your application code */
    while (1) 
    {
		ADCSRA |= (1<<ADSC);			//start conversion
		while((ADCSRA & (1<<ADIF)) ==0);//wait for the conversion to finish
		val = ADC;

		if(val > 512)
		{
			PORTD = 0x03;

			DC = (unsigned char)((100.0*val)/1023);
			updateDC(DC);
		}

		else
		{
			PORTD = 0x05;
			DC = (unsigned char)((100.0*(1023-val))/1024);
			updateDC(DC);
		}
		_delay_ms(1000);
    }
}

void initatePWM()
{
	
	DDRB |= (1<<DDB1);//set PB1 as output

	TCCR1A |= (1<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<FOC1A)|(0<<FOC1B)|(1<<WGM11)|(0<<WGM10);

	// Start timer with pre-scaler 64
	TCCR1B |= (0<<ICNC1)|(0<<ICES1)|(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(1<<CS10);
	
	//TOP =  (F_CPU / (N * F_pwm)) - 1, where N is the prescaler = 64, and F_pwm is the desired 50Hz frequency.
	ICR1 = 4999;

}

void ADCinit()
{
	DDRC &= ~(0<<DDC0);// set PC0 as input
	ADCSRA = 0x87;			//enable ADC and CLK/128
	ADMUX = (1<<REFS0);		//VCC as the reference
}
void updateDC(unsigned char DC)
{
	OCR1A = (unsigned short)((DC * 4999.0)/100.0);
}
