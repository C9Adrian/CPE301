;
; DA2_3.asm
;
; Created: 2/26/2018 11:30:48 AM
; Author : Adrian
;
;delay with timer0
;16MHz

.CSEG

.equ five = 0x05;
.equ ten = 0x0A;
.def clock = r19;
.def zero = r0;


; Replace with your application code
main:
	clr clock		;clear registers
	clr zero
	clr r23
	ldi r22, 0xFF	

	out DDRD, r22	;set PD 0 -7 to output
	ldi r22, 0x31
	out DDRB, r22	;set PB4 and PB5 to output 

	loop:
		out TCNT0, zero;Load TIMER0 = 0
		out TCCR0A, zero;TIMER0: normal mode, internal clock 
	 
		ldi r23,(1<<CS00);enable timer
		ori r23, 0x04
		out TCCR0B, R23

		clr r26; r26 = 0
		ldi r24, 7; r24 = 7

		;create a nested for loop
		delay:
			out TCNT0, zero ;load timer0 = 0
			CALL againloop
			inc r26
			cp r26, r24
			brlt delay			;while r26 < 7

		ldi r26,95			;set tcnto to 95
		out TCNT0, r26
		delay2:					;loop until tov0 is set
			in r25, TIFR0
			sbrs r25, 0
			rjmp delay2

		;disable timer and clear tov0 flag
		ldi r25, (1<<TOV0)
		out TIFR0, r25
		clr r25	
		out TCCR0B, r25		;disable the timer0

		ldi r25, 0xFF		;r25 = 255
		eor clock, r25		;toggle the pulse

		;check if the clock is posedge/negedge
		cp clock, zero
		breq negedge			;if clock == 0

		inc r17
		inc r18

		call check_tog_5

		call check_tog_10

		;output to portB
		clr r25
		;r25 bit 0 is set since posedge
		ori r25, 0x01	;r25=0000 0001
		or r25, r20
		or r25, r21
		out PORTB, r25

		inc r16 ;count++
		out PORTD,r16

		negedge:
			in r25, PORTB
			ldi r26, 0x01	;exor PORTB which is the clock
			eor r25, r26
			out PORTB, r25	;output to PORTB
		rjmp loop
	end:
		rjmp end

    rjmp main

	againloop:
		again: 
			in r25, TIFR0
			sbrs r25, 0
			rjmp again
		ldi r25, (1<<TOV0)
		out TIFR0, r25
	ret

	check_tog_5:
		ldi r25, five
		cp r17, r25
		brne not5
		ldi r25, 0x10
		clr r17
		eor r20, r25
		not5:
	ret

	check_tog_10:
		ldi r25, five
		cp r18, r25
		brne not10
		ldi r25, 0x20
		clr r18
		eor r21, r25
		not10:
		ret 