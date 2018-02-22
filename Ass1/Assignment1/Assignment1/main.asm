;
; Assignment1.asm
;
; Created: 2/10/2018 1:32:30 PM
; Author : Adrian
;

; Replace with your application code
	ldi r16, high(RAMEND)
	out SPH,r16
	ldi r16, low(RAMEND)
	out SPL,r16

start:
	;set stack pointer z to the staring addreass	
	ldi ZL, low(0x0222)
	ldi ZH, high(0x0222)
	ldi YL, low(0x0400)
	ldi YH, high(0x0400)
	ldi XL, low(0x0600)
	ldi XH, high(0x0600)
	clr r16
	clr r20
	clr r21
	clr r22

	ldi r20, low(301)
	ldi r21, high(301)

	
	;loop that places numbers in the array
loop1:
	
	add r22, ZL		;add high and low 
	add r22, ZH
	st Z, r22		;store number
	mov r23, r22

	jmp div

reset:
	adiw ZL, 1	
	clr r22
	dec r20			;inc counter		;check to see if the counter is equal to 300
	brne loop1		;if it isn't the countine placing numbers
	cpi r21,0		;this function checks to see if the counter needs to be reset
	brne checknum
	jmp done		;else its done;

done:
	jmp done

checknum:
	ldi r20,0xFF	;reset counter
	ldi r21, 0
	jmp loop1

div:
	clr r24
	ldi r24, 5		;store r24
	mov r25, r24	;r25 = r24

	divloop:
		cp r22, r24 ;check to if r22%5
		breq pos5 ; if remainder = 0 then divisable 
		brlo neg5	;r22 < 5, then not div.
		add r24, r25 ;r24 + 5
		brcs neg5	;if add op creates carry then not div. 
		jmp divloop	;loop again

	pos5:
		add r16, r22	;add the div by 5 numbers and store in mem
		adc r17, r0
		st Y+, r22
		jmp divdone

	neg5:
		add r18, r22 ;add the not div by 5 numbers and store in mem
		adc r19, r0
		st X+, r22
		jmp divdone

	divdone:
		jmp reset