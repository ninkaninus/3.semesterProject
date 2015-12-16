Hastigheds_kontrol:

		lds	R17, Pulse_Time_H
		
		cpi		R17,	HIGH(Periode_Too_Slow)
		brsh	Too_Slow

		cp		R16,	R17
		brsh	Speed_High

		sub		R17,	R16
		
		in		R16,	OCR2
		
		inc		R16
		
		cpi		R17,	5
		brlo	SPEED_OUT
		
		inc		R16
		
		cpi		R17,	15
		brlo	SPEED_OUT
		
		inc		R16
		
		cpi		R17,	25
		brlo	SPEED_OUT
		
		inc		R16
		
		cpi		R17,	35
		brlo	SPEED_OUT

		inc		R16


rjmp	SPEED_OUT

Speed_High:
		
		sub		R17,	R16
		neg		R17

		in		R16,	OCR2
		
		dec		R16
		
		cpi		R17,	5
		brlo	SPEED_OUT
		
		dec		R16
		
		cpi		R17,	15
		brlo	SPEED_OUT
		
		dec		R16
		
		cpi		R17,	25
		brlo	SPEED_OUT
		
		dec		R16
		
		cpi		R17,	35
		brlo	SPEED_OUT
		
		dec		R16
;		subi	R16,	20
;		brmi	NEGATIV	
rjmp	SPEED_OUT
		
NEGATIV:

		ldi		R16,	0

SPEED_OUT:

		cp		R16,	R18
		brlo	Low_Speed

		cp		R16,	R19
		brsh	Full_Speed

		out		OCR2,	R16
ret

Full_Speed:

		out		OCR2,	R18

ret

Low_Speed:

		out		OCR2,	R19

ret

Too_Slow:

		ldi		R16,	Motor_Too_Slow
		out		OCR2,	R16
		
ret
