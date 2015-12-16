;Den her fil checker hvilken slags banetype bilen befinder sig på. Den nuværende banetype sættes over I R16.

Gyro_Kontrol:


call	MPU6050_Read_Gyro_Z
		lds		R17,		GYRO_ZOUT_H					;Indlæs værdien for Gyro
		mov		Gyro,		R17
		sbrc	Gyro,		7
		neg		Gyro
		
		cpi		Gyro,		Gyro_Stort_Sving			;Værdien for gyro ved stort sving
		brsh	Fortegns_test


LIGEUD:													;Hvis banetypen bestemmes til at være et lige stykke starter dette kontinuære loop,
;														som AI_Check_Laper om accelerometeret angiver et sving. Når bilen kommer ind i et sving
;														hopper den til skift

		ldi		R16,		3							;Sætter typen til 0

ret


Fortegns_test:
		sbrs	R17,		7
rjmp	Venstre_Sving									;Hopper til venstre sving hvis fortegnet siger at det er et venste sving

;Ellers er det et højre sving.

		cpi		Gyro,		Gyro_Lille_Sving	;Værdi for gyro til lille sving
		brsh	RIGHT_TURN_SMALL				;Hvis gyroværdien er stor nok til et lille sving, så skifter den type.

		ldi		R16,		4			;Sætter vejtypen til stor højre
		
ret

RIGHT_TURN_SMALL:

		ldi		R16,		5			;Sætter vejtypen til lille højre.
		
ret

Venstre_Sving:

		cpi		Gyro,		Gyro_Lille_Sving	;Værdi for gyro til lille sving
		brsh	LEFT_TURN_SMALL				;Hvis gyroværdien er stor nok til et lille sving, så skifter den type.

		ldi		R16,		2			;Sætter vejtypen til stor venstre
		
ret

LEFT_TURN_SMALL:

		ldi		R16,		1			;Sætter vejtypen til lille venstre.
		
ret

;----------------------------------------------------------------------

Gyro_Mean:

call	MPU6050_Read_Gyro_Z
		lds		R10,		GYRO_ZOUT_H	;Indlæs værdien for gyro
		sbrc	R10,		7
		neg		R10
		
		ldi		R16, 1
call	Delay_MS
		
call	MPU6050_Read_Gyro_Z
		lds		R11,		GYRO_ZOUT_H	;Indlæs værdien for gyro
		sbrc	R11,		7
		neg		R11
	
		add		R10,	R11
		ror		R10
				
		mov		R16, R10
		
ret
