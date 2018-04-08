/* This is actually the Midterm. I saved it as DA4. 
 * DA4.c
 *
 * Created: 4/4/2018 9:26:15 PM
 * Author : Adrian
 */  

#ifndef F_CPU
#define F_CPU 16000000UL					//set clock speed
#endif

#ifndef BAUD
#define BAUD 9600						//set Baud rate
#endif

#define BAUD_PRESCALLER (((F_CPU / (BAUD *16UL)))-1)

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "ioe.h"

void usart_send(unsigned char);
unsigned char usart_recive();
void send_AT(unsigned char[]);

volatile unsigned int adc_temp;
volatile unsigned int tempFar;
volatile char RecievedChar;

	unsigned char AT[] = "AT\r\n";														//check if at commands are instlled
	unsigned char ATCWMODE []= "AT+CWMODE=1\r\n";										//enable CWmode
	unsigned char ATCWJAP[] = "AT+CWJAP=\"Ruiz\",\"_*******\"\r\n";						//Connect to an access point, password blurred
	unsigned char CIPMUX[] = "AT+CIPMUX=1\r\n";											//
	unsigned char CIPSTART[] = "AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",80\r\n";	//connect to the thingspeak
	unsigned char CIPSEND[] = "AT+CIPSEND=0,44\r\n";									//sending to port 0 and allow 44 bytes to be sent
	unsigned char SEND_DATA[] ="GET /update?key=***********=";							//update the channel, key blurred

char outs[2];
int main(void)
{
    /* Replace with your application code */
	//adc_init();
	//USART_init();

	//Write API key SVZYIVAYBLWDH86F

	usart0_init_();					//initialize usart
	adc_init();						//initialize adc
	
	
	DDRC = 0b00000000;

	_delay_ms(500);						
	printm(AT);					//send AT to the USART

	//connect to network
	_delay_ms(2000);
	printm("AT+CWMODE=1\r\n");	//send AT commands to the USRAT
	_delay_ms(2000);
	printm("AT+CWJAP=\"Ruiz\",\"_***********\"\r\n");


	_delay_ms(6000);
	printm(ATCWMODE);
	_delay_ms(10000);
	printm(CIPMUX);
	_delay_ms(10000);
	sei();					//enable interrupts

	while(1)
	{

	}
}


//Setup The ADC
void adc_init()
{
	ADMUX =0;
	ADCSRA= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);	//sample rate of 125kHz at 16MHz
	ADMUX |= (1<<REFS0);							//Set ADC reference to AVCC
	ADMUX |= (1<<ADLAR);							//Left adjust ADC Result to allow 8 bit reading
	
	ADCSRA |= (1<<ADIE);							//set ADC to intruppt mode
	ADCSRA |= (1<<ADEN);							//Enable ADC
	ADCSRA |= (1<<ADATE);							//set ADC auto trigger enable
	ADCSRB = 0;										//0 for free running mode
	ADCSRA |= (1<<ADSC)	;							//start A2D Conversions
	
	
}


//Intrupt subrotine for adc
ISR(ADC_vect)
{
	adc_temp = ADCH;					//grab voltage
	adc_temp = (5*adc_temp*100/1024);	//calculate temperature from voltage in celuis
	adc_temp = adc_temp * (2);
	adc_temp = adc_temp +32;			//convert to far.

	sprintf(outs,"%d",adc_temp);		//convert the far to string
	
	//at commandss
	printm(CIPSTART);
	_delay_ms(2000);
	printm(CIPSEND);
	_delay_ms(5000);
	printm(SEND_DATA);
	printm(outs);				//send temp to usart
	printm("\n");
	_delay_ms(5000);
	printm("AT+CIPCLOSE=0\r\n");	//close the channel
	_delay_ms(5000);
	printm("AT+CIPCLOSE\r\n");
	_delay_ms(5000);

	_delay_ms(1000);					//delay
}
