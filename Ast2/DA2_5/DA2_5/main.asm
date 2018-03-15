;
; DA2_5.asm
;
; Created: 3/14/2018 5:46:37 PM
; Author : Adrian
;
.org 0		;start
	rjmp start

.org 0x02	;location for ext_int0
	rjmp ex0_isr

.def temp = r20
; Replace with your application code
start:
	ldi temp, high(ramend)
	out sph, temp
	ldi temp, low(ramend)
	out spl, temp

	sbi ddrb, 5
	sbi portd, 2
	ldi temp, 1<<INT0	;enable int0

	out eimsk, temp
	sei

main:	rjmp main

ex0_isr:
	ldi temp, 1<<INTF0
	out eifr, temp
	sbi portb, 5
	call delay_500ms
	cbi portb, 5
	reti

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