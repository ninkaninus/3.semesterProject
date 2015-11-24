.MACRO WheelSpeed_Init
			ldi		R16, 0x00
			out		TCCR1A, R16
			ldi		R16, 0b00000010			; Falling edge triggered, 1/1024 prescaling
			out		TCCR1B, R16	

			clr		R16
			sts		Edge1_L, R16
			sts		Edge1_H, R16
			sts		Pulse_Time_L, R16
			sts		Pulse_Time_H, R16

			sts		Ticks_L, R16
			sts		Ticks_H, R16

			in		R16, TIMSK
			ori		R16, (1<<TICIE1)		;Enable interrupt on output compare match for timer0
			out		TIMSK, R16				;Timer/interrupt masking register

.ENDMACRO



Input_Capture:

			Push_Register_5 R0, R1, R2, R3, R16
			push	R17
			lds		R0, Ticks_L
			lds		R1, Ticks_H
			
			ldi		R16, 0x01
			add		R0, R16
			ldi		R16, 0x00
			adc		R1, R16
			
			sts		Ticks_L, R0
			sts		Ticks_H, R1	
			
			lds		R16, Pulse
			cpi		R16, 1
			breq	Edge1
			
			cpi		R16, 4
			breq	Edge2
			
			inc		R16
			sts		Pulse, R16
			
			rjmp	WheelSpeed_End
			
			lds		R16, SREG_1			
			sbrc	R16, 0							; bit 0 represents the current edge that's being measured - 0 = EDGE1, 1 = EDGE2
			rjmp	EDGE2
			
EDGE1:		inc		R16
			sts		Pulse, R16

			in		R0, ICR1L
			in		R1, ICR1H
			
			sts		Edge1_L, R0
			sts		Edge1_H, R1

			lds		R16, SREG_1
			sbr		R16, 0b00000001					; set bit 0 in R16 (performs a logical ORI instruction)
			sts		SREG_1, R16
			
			rjmp	WheelSpeed_End
			
EDGE2:		ldi		R16, 1
			sts		Pulse, R16

			lds		R0, Edge1_L
			lds		R1, Edge1_H
			
			in		R2, ICR1L
			in		R3, ICR1H
			
			sub		R2, R0
			sbc		R3, R1
			
			ldi		R16, high(6000)
			cp		R3, R16
			brlo	WheelSpeed_End		
			
			sts		Pulse_Time_L, R2
			sts		Pulse_Time_H, R3
			
			lds		R16, SREG_1
			cbr		R16, 0b00000001					; clear bit 0 in R16 (performs logical AND with complement of operand)
			sts		SREG_1, R16
			
			ldi		R16, 0x00
			out		TCNT1H, R16						; Temp = R16
			out		TCNT1L, R16						; TCNT1L = R16 & TCNT1H = Temp	

			call	Hastigheds_kontrol
			
WheelSpeed_End:

			call AI_Hall		;Alt AI der har med ticks at gøre ligger her
			
			pop R17

			Pop_Register_5 R16, R3, R2, R1, R0
			
			reti
