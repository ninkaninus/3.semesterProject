AI_Lap:

	lds		R17,	AI_Check_Lap
	inc		R17							;Runde tæller
	sts		AI_Check_Lap,	R17

	cpi		R17,	1
	breq	Mapping
	
	cpi		R17,	3
	brsh	Run_Time

;First round							Vi sætter der første stykke bane oveni, så vi ikke løber tør for bane.

		mov		R16,		YL
		mov		R17,		YH
		ldi		YH,			HIGH(Map_Start)		
		ldi		YL,			LOW(Map_Start)		

		ld			R18,		Y+		;Length_L
		ld			R19,		Y+		;Length_H
		ld			R20,		Y+		;Type
		
		mov		YL,			R16
		mov		YH,			R17

		cp			R20,		Type
		breq		Same_Type_First_And_Last

		st		Y+,		Length_L
		st		Y+,		Length_H
		st		Y+,		Type

		st		Y+,		R18
		st		Y+,		R19
		st		Y+,		R20
		

rjmp		Run_Time
		
Same_Type_First_And_Last:

		add		Length_L,	R18
		adc		Length_H,	R19
		
		st		Y+,		Length_L
		st		Y+,		Length_H
		st		Y+,		Type
		
Run_Time:

		ldi		YH,			HIGH(Map_Start)		
		ldi		YL,			LOW(Map_Start)		

		ld			Length_L,		Y+
		ld			Length_H,		Y+
		ld			Type,			Y+

ret

Mapping:

		ldi		YH,			HIGH(Map_Start)		
		ldi		YL,			LOW(Map_Start)	

call	Gyro_Kontrol
		mov		Type,		R16

ret
