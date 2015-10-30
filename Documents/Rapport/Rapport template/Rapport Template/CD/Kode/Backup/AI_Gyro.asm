;Den her fil checker hvilken slags banetype bilen befinder sig på

Gyro_Kontrol:


call	Gyro_Mean										;Indlæser gennemsnitsværdien af to gyro læsninger, gemmer resultatet i R16, benytter R10,R11 og R17.
		
		cpi		Accel,		Accel_Stort_Sving			;juster værdi, Værdi for acceleration ved stort højre sving
		brsh	Fortegns_test


LIGEUD:													;Hvis banetypen bestemmes til at være et lige stykke starter dette kontinuære loop,
;														som AI_Check_Laper om accelerometeret angiver et sving. Når bilen kommer ind i et sving
;														hopper den til skift
		cpi		Type,		0
		breq	SAME_TYPE
		st		Y+,			Length_L
		st		Y+,			Length_H						;Sæt Længden ind først-
		st		Y+,			Type						;og derefter vejtypen.
		ldi		Type,		0							;Sætter vejtypen til ligeud
		ldi		Length_L,	0
		ldi		Length_H,	0
		
ret


Fortegns_test:

call	MPU6050_Read_Gyro_Z
		lds		R17,		GYRO_ZOUT_H					;Indlæs værdien for accelerometeret, SKAL ÆNDRES TIL GYRO
		sbrs	R17,		7
		
rjmp	LEFT_TURN
		
RIGHT_TURN:												;Hvis banetypen bestemmes til at være et højre sving starter dette kontinuære loop,
;														som AI_Check_Laper om accelerometeret angiver et lige stykke. Når bilen kommer ud af et sving
;														hopper den til skift

		
		cpi		R16,		Accel_Lille_Sving	;juster værdi, Værdi for acceleration ved stort højre sving
		brlo	RIGHT_TURN2				;Hvis gyroværdien er stor nok til et lille sving, så skifter den type.

		ldi		Type,		1			;Sætter vejtypen til lille højre
		
ret

RIGHT_TURN2:							;Hvis banetypen bestemmes til at være et stort højre sving starter dette kontinuære loop,
;										som AI_Check_Laper om accelerometeret angiver et lige stykke. Når bilen kommer ud af et sving
;										hopper den til skift

		cpi		Type,		0
		brne	SAME_TYPE

		st		Y+, 		Length_L
		st		Y+,			Length_H		;Sæt Længden ind først-
		st		Y+,			Type			;og derefter vejtypen.
		ldi		Type,		3				;Sætter vejtypen til stort højre
		ldi		Length_L,	0
		ldi		Length_H,	0
		
ret


LEFT_TURN:								;Hvis banetypen bestemmes til at være et højre sving starter dette kontinuære loop,
;										som AI_Check_Laper om accelerometeret angiver et lige stykke. Når bilen kommer ud af et sving
;										hopper den til skift

		
		cpi		R16,		Accel_Lille_Sving	;juster værdi, Værdi for acceleration ved stort højre sving
		brlo	LEFT_TURN2				;Hvis gyroværdien er stor nok til et lille sving, så skifter den type.

		ldi		Type,		2			;Sætter vejtypen til lille venstre
		
ret

LEFT_TURN2:							;Hvis banetypen bestemmes til at være et stort højre sving starter dette kontinuære loop,
;										som AI_Check_Laper om accelerometeret angiver et lige stykke. Når bilen kommer ud af et sving
;										hopper den til skift

		cpi		Type,		0
		brne	SAME_TYPE
		
		st		Y+,			Length_L
		st		Y+,			Length_H		;Sæt Længden ind først-
		st		Y+,			Type			;og derefter vejtypen.
		ldi		Type,		4				;Sætter vejtypen til stort venstre
		ldi		Length_L,	0
		ldi		Length_H, 	0
		
ret

;------------------------------


SAME_TYPE:

ret

Gyro_Mean:

call	MPU6050_Read_Gyro_Z
		lds		R10,		GYRO_ZOUT_H	;Indlæs værdien for accelerometeret, SKAL ÆNDRES TIL GYRO
		sbrc	R10,		7
		neg		R10
		
		ldi		R16, 1
call	Delay_MS
		
call	MPU6050_Read_Gyro_Z
		lds		R11,		GYRO_ZOUT_H	;Indlæs værdien for accelerometeret, SKAL ÆNDRES TIL GYRO
		sbrc	R11,		7
		neg		R11
	
		add		R10,	R11
		ror		R10
				
		mov		R16, R10
		
ret
