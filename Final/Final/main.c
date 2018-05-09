#define F_CPU 8000000UL
/**
*/

#define F_CPU 8000000UL		//!< clock speed of Atmega328p - 8MHz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "drive_motor.h"
#include "uart.h"

void control_bot(){ // controls everything on bot
	
	readString();
	if(done)
	drive_motor(l, r);
	else
	drive_motor(0, 0);
	
}

int main(void){
	// initialize WIFI 
	initUART();
	init_motor();
	
	

	while(1){
		control_bot();
	}
}
