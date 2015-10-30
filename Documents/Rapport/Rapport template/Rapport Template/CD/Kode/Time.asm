; This library handles all initial setup of timer operations

; Initialize timer0 to generate an output compare interrupt every 1[ms]
.MACRO Time_Init
			ldi		R16, 0b00001011			; CTC-mode, 1/64 prescaling -> 250 cycles pr ms.
			out		TCCR0, R16
			ldi		R16, 0x00
			out		TCNT0, R16				; Counter0 initialization
			ldi		R16, 249				; 249+1 cycles = 1[ms] for every output compare match
			out		OCR0, R16
			
			clr		R16
			sts		Timer_1ms_L, R16
			sts		Timer_1ms_M, R16
			sts		Timer_1ms_H, R16	

			in		R16, TIMSK
			ori		R16, (1<<OCIE0)			;Enable interrupt on output compare match for timer0
			out		TIMSK, R16				;Timer/interrupt masking register
			
.ENDMACRO

; Timer subroutines

Timer0_Update:
			push	R16
			in		R16, SREG
			push	R16
			
			ldi		R16, 0x01
			lds		R0, Timer_1ms_L			
			add		R0, R16						;Advance time by 1ms whenever timer0 has compare match
			sts		Timer_1ms_L, R0	
			brcc	Timer_Update_End
			
			ldi		R16, 0x00
			lds		R1, Timer_1ms_M				;24 bits = 16777 seconds = 4.6 hours... ish :D
			adc		R1, R16
			sts		Timer_1ms_M, R1	
			brcc	Timer_Update_End
			
			lds		R2, Timer_1ms_H
			adc		R2, R16
			sts		Timer_1ms_H, R2
			brcc	Timer_Update_End
			
Timer_Update_End:

			pop		R16
			out		SREG, R16
			pop		R16
			
			reti
			

