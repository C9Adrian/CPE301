;
; DA2_2.asm
;
; Created: 3/5/2018 6:47:56 PM
; Author : Adrian


; Replace with your application code
.org 0x0000;

;PB5 is LED 
;PB7 is Switch
.def temp = r17

ldi r16, high(ramend)
out sph, r16
ldi r16, low(ramend)
out spl, r16

ldi r16, 0xFF
out ddrb, r16
ldi r16, 0xFF
out portb, r16


start:
	ldi temp, 0xFF
	out ddrb, temp			
	ldi temp, 0b11111110 ;set pin0 on port d to input
	out ddrd, temp

	clr temp
	out portb, temp			;set all pins on porb to low state
	ldi temp, 0b00000001
	out portb, temp			;set all pins to low

main:
	in temp, pind			;get the stae of pins on Port D
	andi temp, (1<<pd0)
	cpi temp, 0				;cmp result to 0 ( pushbutton is pressed)
	brne main				;if not then keep looping
	ldi temp, (1<<pb5)		;load the value into pibb5
	out pinb, temp
	call delay_1s			;delay the light on for 1 second
	cbi portb, 5			;turn pin off
	rjmp main				

delay_1s:
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