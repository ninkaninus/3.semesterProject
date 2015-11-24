;Den her fil er hastighedskontrol.

Hastigheds_kontrol:				;Skal bruge R16 som den satte periode, og R17 som den nuværende periode, og R18 som hastighed_out.


		lds	R17, Pulse_Time_H

		cp		R17,	R16
		brlo	SPEED_IS_HIGH	;The speed is too high

;SPEED_IS_LOW:					;R17>R16

		sub		R16,	R17
		ldi		R17,	1
		cpi		R16,	10
		brlo	HASTIGHED_SET_LOW
		ldi		R17,	1
		cpi		R16,	20
		brlo	HASTIGHED_SET_LOW
		ldi		R17,	1
		cpi		R16,	30
		brlo	HASTIGHED_SET_LOW
		ldi		R17,	1
		cpi		R16,	40
		brlo	HASTIGHED_SET_LOW
		ldi		R17,	1
		
HASTIGHED_SET_LOW:
		
		in		R16,	 OCR2
		add		R16,	R17
		brcs	FULD_KRAFT
;		lds		R17,	AI_Hastighed_D
		add		R16,	R17
		brcs	FULD_KRAFT
		out		OCR2,	R16

ret



SPEED_IS_HIGH:						;R16>R17

		sub		R17,	R16
		mov		R16,	R17
		ldi		R17,	1
		cpi		R16,	10
		brlo	HASTIGHED_SET_HIGH
		ldi		R17,	1
		cpi		R16,	20
		brlo	HASTIGHED_SET_HIGH
		ldi		R17,	1
		cpi		R16,	30
		brlo	HASTIGHED_SET_HIGH
		ldi		R17,	1
		cpi		R16,	40
		brlo	HASTIGHED_SET_HIGH
		ldi		R17,	1

HASTIGHED_SET_HIGH:

		in		R16,	OCR2
		cp		R16,	R17
		brlo	Too_low
		sub		R16,	R17
;		lds		R17,	AI_Hastighed_D
		add		R16,	R17
		cpi		R16,	5
		brlo	Too_low
		out		OCR2,	R16

ret

Too_low:	ldi		R16, 5
			out		OCR2, R16
ret


FULD_KRAFT:
		ldi		R16,	255
		out		OCR2,	R16
		
ret






