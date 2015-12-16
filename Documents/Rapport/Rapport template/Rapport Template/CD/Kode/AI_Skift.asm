SKIFT_TEST:

		ldi		R16,	1
		add		Length_L,	R16
		ldi		R16,	0
		adc		Length_H,	R16

		call	Gyro_Kontrol

		Cp		R16,		Type
		breq	SAME_TYPE
		
		cpi		R16,		1		;Skift Type
		breq	LILLE_V
		
		cpi		R16,		2
		breq	LEFT_SKIFT			;Skift til venstre sving
		
		cpi		R16,		3
		breq	STRAIGHT_SKIFT		;Skift til lige ud

		cpi		R16,		4
		breq	RIGHT_SKIFT			;Skift til højre sving
		
		cpi		R16,		5		;Skift Type
		breq	LILLE_H
		
LILLE_V:

		ldi		Type,		1
ret

LILLE_H:

		ldi		Type,		5
ret

SAME_TYPE:

ret

LEFT_SKIFT:

		cpi		Type,	1
		breq	SAME_TYPE
		
		st		Y+,		Length_L
		st		Y+,		Length_H
		st		Y+,		Type
		ldi		Length_L,		0
		ldi		Length_H,		0
		ldi		Type,			2

ret

STRAIGHT_SKIFT:



		st		Y+,		Length_L
		st		Y+,		Length_H
		st		Y+,		Type
		ldi		Length_L,		0
		ldi		Length_H,		0
		ldi		Type,			3

ret

RIGHT_SKIFT:


		cpi		Type,	5
		breq	SAME_TYPE


		st		Y+,		Length_L
		st		Y+,		Length_H
		st		Y+,		Type
		ldi		Length_L,		0
		ldi		Length_H,		0
		ldi		Type,			4

ret


