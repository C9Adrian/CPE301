;
; DA2_4.asm
;
; Created: 3/6/2018 10:13:22 PM
; Author : Adrian
;


; Replace with your application code
.def temp = r20

.org 0x0
	rjmp start
.org 0x20 
	rjmp TIM0_OVF_ISR

.org 0x100

start:
    ldi temp, high(ramend)
	out sph, r20
	ldi temp, low(ramend)
	out spl, r20

	ldi r16, 0xFF
	out DDRD, r16


main:
	ldi temp, 0xF2		;load timer0
	out tcnt0, temp

	ldi temp, 0x00
	out tccr0a, temp		;timer0, normal mode, int clk
	
	ldi temp, (1<<CS02 | 1<<CS00)
	out tccr0b, temp		;pre-scalar = clk/1024
	
	ldi r20, 0x01

	ldi r16, 0x20
	sts timsk0, r16
	sei
	again:
		rjmp again

TIM0_OVF_ISR:
	sbi portb, 5 
	reti