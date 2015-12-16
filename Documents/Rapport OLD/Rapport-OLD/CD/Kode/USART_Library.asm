 ; USART_library.asm
 ; Author: StjerneIdioten

.MACRO  USART_Init
	;Set Baud Rate to 9600
	ldi R16,	@1	
	ldi R17,	@0

	out	UBRRH,	R17
	out UBRRL,	R16

	;Enable receiver and transmitter
	ldi R16,	(1<<RXEN)|(1<<TXEN)|(1<<RXCIE)
	out	UCSRB,	R16

	;Set frame format: 8data, 1stop bit
	ldi	R16,	(1<<URSEL)|(3<<UCSZ0)
	out	UCSRC,	R16
.ENDMACRO

 ;Waits for an empty transmit buffer and then moves R16 to the transmit buffer
 USART_Transmit: 
 USART_Transmit_Start:
	; Wait for empty transmit buffer
	sbis	UCSRA,	UDRE
	rjmp	USART_Transmit_Start
	out	UDR, R16
ret


;Waits for a byte to be recived and outputs it to R16
USART_Receive:
USART_Receive_Start:
	; Wait for data to be received
	sbis UCSRA, RXC
	rjmp USART_Receive_Start
	; Get and return received data from buffer
	in r16, UDR
ret


;Outputs a newline to serial. In the format of '\r\n'
.Macro USART_Newline
	ldi R16, 0x0D
	call USART_Transmit 
	ldi R16, 0x0A
	call USART_Transmit 
.ENDMACRO


;Outputs the byte in R16 as a string of 8 ascii 1's or 0's
USART_Binary:
	mov R17, R16			;Copy R16 to R17
	ldi R18, 0x00			;Set the counter to zero
USART_Binary_Loop:
	sbrs R17, 7				;Skip if bit 7 in R17 is set
	rjmp USART_Binary_0		;Jump here if the it was 0
	ldi R16, '1'			;Load in ascii 1 in R16
	call USART_Transmit		;Transmit the 1
	rjmp USART_Binary_End	;Jump to the end
USART_Binary_0:				
	ldi R16, '0'			;Load in ascii 0 in R16
	call USART_Transmit
USART_Binary_End:
	lsl R17					;Left shift R17
	inc R18					;Increment R18
	cpi R18, 0x08			;Check if we have converted and sent an entire byte yet
	brne USART_Binary_Loop	;Repeat if we haven't
ret



;Expecs a 16 bit value in R17:R16
USART_Decimal_S16:

	movw R19:R18, R17:R16
	sbrs R19, 7
	rjmp USART_Decimal_S16_Count_10000

USART_Decimal_S16_Signed:
	ldi R16, '-'
	call USART_Transmit
	subi R18, 0x01
	sbci R19, 0x00
	com R18
	com R19

USART_Decimal_S16_Count_10000:
	clr R20
	ldi XH, HIGH(10000)
	ldi XL, LOW(10000)
USART_Decimal_S16_Count_10000_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_S16_Count_10000_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_S16_Count_1000:
	clr R20
	ldi XH, HIGH(1000)
	ldi XL, LOW(1000)
USART_Decimal_S16_Count_1000_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_S16_Count_1000_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_S16_Count_100:
	clr R20
	ldi XH, HIGH(100)
	ldi XL, LOW(100)
USART_Decimal_S16_Count_100_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_S16_Count_100_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_S16_Count_10:
	clr R20
	ldi XH, HIGH(10)
	ldi XL, LOW(10)
USART_Decimal_S16_Count_10_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_S16_Count_10_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_S16_Count_1:
	clr R20
	ldi XH, HIGH(1)
	ldi XL, LOW(1)
USART_Decimal_S16_Count_1_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_S16_Count_1_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

ret


;Expecs a 16 bit value in R17:R16
USART_Decimal_16:

	movw R19:R18, R17:R16

USART_Decimal_16_Count_10000:
	clr R20
	ldi XH, HIGH(10000)
	ldi XL, LOW(10000)
USART_Decimal_16_Count_10000_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_16_Count_10000_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_16_Count_1000:
	clr R20
	ldi XH, HIGH(1000)
	ldi XL, LOW(1000)
USART_Decimal_16_Count_1000_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_16_Count_1000_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_16_Count_100:
	clr R20
	ldi XH, HIGH(100)
	ldi XL, LOW(100)
USART_Decimal_16_Count_100_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_16_Count_100_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_16_Count_10:
	clr R20
	ldi XH, HIGH(10)
	ldi XL, LOW(10)
USART_Decimal_16_Count_10_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_16_Count_10_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_16_Count_1:
	clr R20
	ldi XH, HIGH(1)
	ldi XL, LOW(1)
USART_Decimal_16_Count_1_Loop:
	inc R20
	sub R18, XL
	sbc R19, XH
	brcc USART_Decimal_16_Count_1_Loop
	dec R20
	add R18, XL
	adc R19, XH
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

ret

;Expecs a 8 bit value in R16
USART_Decimal_8:

	mov R18, R16

USART_Decimal_8_Count_100:
	clr R20
	ldi R17, 100
USART_Decimal_8_Count_100_Loop:
	inc R20
	sub R18, R17
	brcc USART_Decimal_8_Count_100_Loop
	dec R20
	add R18, R17
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_8_Count_10:
	clr R20
	ldi R17, 10
USART_Decimal_8_Count_10_Loop:
	inc R20
	sub R18, R17
	brcc USART_Decimal_8_Count_10_Loop
	dec R20
	add R18, R17
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_8_Count_1:
	clr R20
	ldi R17, 1
USART_Decimal_8_Count_1_Loop:
	inc R20
	sub R18, R17
	brcc USART_Decimal_8_Count_1_Loop
	dec R20
	add R18, R17
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

ret















;Expecs a S8 bit value in R16
USART_Decimal_S8:

	mov R18, R16
	sbrs	R18,	7
	rjmp	USART_Decimal_S8_Count_100
	
	ldi		R16,	'-'
call	USART_Transmit

	dec		R18
	com		R18

USART_Decimal_S8_Count_100:
	clr R20
	ldi R17, 100
USART_Decimal_S8_Count_100_Loop:
	inc R20
	sub R18, R17
	brcc USART_Decimal_S8_Count_100_Loop
	dec R20
	add R18, R17
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_S8_Count_10:
	clr R20
	ldi R17, 10
USART_Decimal_S8_Count_10_Loop:
	inc R20
	sub R18, R17
	brcc USART_Decimal_S8_Count_10_Loop
	dec R20
	add R18, R17
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

USART_Decimal_S8_Count_1:
	clr R20
	ldi R17, 1
USART_Decimal_S8_Count_1_Loop:
	inc R20
	sub R18, R17
	brcc USART_Decimal_S8_Count_1_Loop
	dec R20
	add R18, R17
	ldi R16, 0x30
	add R16, R20
	call USART_Transmit

ret
