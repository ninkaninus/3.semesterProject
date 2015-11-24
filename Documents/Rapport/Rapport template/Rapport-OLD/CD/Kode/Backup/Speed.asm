Hastigheds_kontrol:

		sub		R16, R17						; R16 = Ønsket pulstid, R17 = Sidst målte pulstid
		brpl	TooLow								; Hvis resultatet er positivt, er den aktuelle pulstid for lav, branch til low
		
; Den aktuelle pulstid er for høj
TooHigh:neg 	R16
		;cpi		R16, 3
		;brlo	Speed_End
		
		ldi		R20, 2
		
		cpi		R16, 6
		in		R17, SREG
		sbrs	R17, 0
		ldi		R20, 2
		
		cpi		R16, 9
		in		R17, SREG
		sbrs	R17, 0
		ldi		R20, 4
		
		cpi		R16, 10
		in		R17, SREG
		sbrs	R17, 0
		ldi		R20, 8
				
		in		R17, OCR2
		add		R17, R20
		cpi		R17, 240
		brsh	Speed_End
		out		OCR2, R17
		
		rjmp	Speed_End

; Den aktuelle pulstid er for lav
TooLow:	;cpi		R16, 3
		;brlo	Speed_End
		
		ldi		R20, 2
		
		cpi		R16, 4
		in		R17, SREG
		sbrs	R17, 0
		ldi		R20, 2
		
		cpi		R16, 6
		in		R17, SREG
		sbrs	R17, 0
		ldi		R20, 4
		
		cpi		R16, 8
		in		R17, SREG
		sbrs	R17, 0
		ldi		R20, 8	
		
		in		R17, OCR2
		sub		R17, R20
		cpi		R17, 15
		brlo	Speed_End
		out		OCR2, R17
		
Speed_End:

;		ldi		R16, 20
;		call	Delay_MS
		
;		inc		ZH
;		cpi		ZH, 10
;		brlo	Speed_End2
		
		ret
		
Speed_End2:

		clr		ZH
		
		call	MPU6050_Read_Gyro_Z
		lds		R16, GYRO_ZOUT_L
		lds		R17, GYRO_ZOUT_H
		call	USART_Decimal_16

		ldi		R16, ','
		call	USART_Transmit
				
		in		R16, OCR2
		call	USART_Decimal_8
				USART_NewLine
				
		ret
