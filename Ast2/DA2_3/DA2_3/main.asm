;
; DA2_3.asm
;
; Created: 3/6/2018 6:26:20 PM
; Author : Adrian
;
.include "M328PDEF.INC"

; Replace with your application code

ldi r16, high(ramend)
out sph, r16
ldi r16, low(ramend)
out spl, r16

sbi ddrb, 5				;PB5 as an output

start:
	sbi portb, 5		;set PINB5 to high
	rcall delay_500ms
	cbi portb, 5		;set PINB5 to low
	rcall delay_500ms
	rjmp start

; this a delay of 500ms without using a timer
; it does about 8000000 cycles which is about .5 seconds in 
;16MHz
delay_500ms:
	ldi r20, 50
		delay2:
			ldi r21, 200
		delay1: 
			ldi r22, 199
		delay0:
			nop
			dec r22
			brne delay0
			nop 
			dec r21
			brne delay1
			dec r20
			brne delay2

ret


	 

