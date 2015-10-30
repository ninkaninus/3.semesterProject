.MACRO EXT1_init
	ldi		R16, (1<<ISC11)						; Falling edge triggered external interrupt
	out		MCUCR, R16
	cbi		DDRD, 3								; PD3 = input
		
			ldi		R16, 0x00
			out		TCCR1A, R16
			ldi		R16, 0b00000010				; Falling edge triggered, 1/8 prescaling (0.5 [us] pr count)
			out		TCCR1B, R16		
	
	clr		R16
	mov		R10, R16
	mov		R11, R16
.ENDMACRO

Input_Capture:

			Push_Register_5 R0, R1, R2, R3, R16

			lds		R16, SREG_1			
			sbrc	R16, 0								; bit 0 represents the current edge that's being measured - 0 = EDGE1, 1 = EDGE2
			rjmp	EDGE2				
			
EDGE1:		in		R0, TCNT1L
			in		R1, TCNT1H
			
			sts		Edge1_L, R0
			sts		Edge1_H, R1

			sbr		R16, 0b00000001					; set bit 0 in R16 (performs a logical ORI instruction)
			sts		SREG_1, R16
			
			Pop_Register_5 R16, R3, R2, R1, R0
			
			reti
			
EDGE2:		lds		R0, Edge1_L
			lds		R1, Edge1_H
			
			in		R2, TCNT1L
			in		R3, TCNT1H
			
			sub		R2, R0
			sbc		R3, R1
			
			ldi		R16, high(3000)
			cp		R3, R16
			brlo	WheelSpeed_End		
			
			lds		R16, SREG_1
			cbr		R16, 0b00000001					; clear bit 0 in R16 (performs logical AND with complement of operand)
			sts		SREG_1, R16
			
			ldi		R16, 0x00
			out		TCNT1H, R16						; Temp = R16
			out		TCNT1L, R16						; TCNT1L = R16 & TCNT1H = Temp	
			
			sts		Pulse_Time_L, R2
			sts		Pulse_Time_H, R3

WheelSpeed_End:
			
			Pop_Register_5 R16, R3, R2, R1, R0

			reti

;EXT1:		ldi		R16, 0x01
			add		R10, R16
			ldi		R16, 0
			adc		R11, R16
			
			ldi		R16, high(840)
			cp		R11, R16
			brne	EXT1_End
			
			ldi		R16, low(840)
			cp		R10, R16
			brne	EXT1_End
			
			ldi		R16, 0
			out 	OCR2, R16
			
;EXT1_End:				
			reti
