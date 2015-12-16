AI_Hall:

	call LED

	lds		R17,	AI_Check_Lap
	
	cpi		R17,	1
	breq	Mapping_Speed
	
	cpi		R17,	2
	brsh	Run_Speed
	
;Ellers preround

		ldi		R16, LOW(Periode_Mapping)	;Reference periode.
		ldi		R17, HIGH(Periode_Mapping)	;Reference periode.
		sts		Speed_L,	R16
		sts		Speed_H,	R17

ret

Mapping_Speed:

call	SKIFT_TEST

ldi		R16, LOW(Periode_Mapping)	;Reference periode.
ldi		R17, HIGH(Periode_Mapping)	;Reference periode.
sts		Speed_L,	R16
sts		Speed_H,	R17

ret

Run_Speed:

call	Read_Map

ret

LED:
	cpi Type, 1
	breq LED_Venstre_L

	cpi Type, 2
	breq LED_Venstre_S

	cpi Type, 3
	breq LED_Ligeud

	cpi Type, 4
	breq LED_Hoejre_S

	cpi Type, 5
	breq LED_Hoejre_L

	ret

	.equ LED_Stort_Hoejre = 0b00100000
	.equ LED_Stort_Venstre = 0b00000010
	.equ LED_Lille_Hoejre = 0b00010000
	.equ LED_Lille_Venstre = 0b00000100
	.equ LED_Lige = 0b00001000
	.equ LED_Alle = 0b00111110

LED_Venstre_L:
	ldi R16, LED_Lille_Venstre
	out PORTA, R16
	ret 

LED_Venstre_S:
	ldi R16, LED_Stort_Venstre
	out PORTA, R16
	ret 

LED_Ligeud:
	ldi R16, LED_Lige
	out PORTA, R16
	ret 

LED_Hoejre_S:
	ldi R16, LED_Stort_Hoejre
	out PORTA, R16
	ret 	

LED_Hoejre_L:
	ldi R16, LED_Lille_Hoejre
	out PORTA, R16
	ret 










