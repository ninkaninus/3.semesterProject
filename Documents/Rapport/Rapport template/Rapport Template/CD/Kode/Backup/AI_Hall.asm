;Denne fil beskriver hvad der skal ske i forhold til AI når bilen har kørt et tick.

AI_HALL_INTERRUPT:							;Interrupt fra hall sensoren der fungerer som et tachometer

		lds		R20, AI_Check_Lap			

		cpi		R20, AI_Lap_Speed			;Checks if we are currently running a speed lap.
		breq	Hall_Speed_Lap

		cpi		R20, AI_Lap_Mapping			;Checks if we are currently running a mapping lap.
		breq	Hall_Map_Lap


		ldi		R20,			100			;Sætter hastigheden til 100, så bilen langsomt bevæger sig mod målstregen uden problemer1
		out		OCR2,			R20	
		
;Bilen skal skuppes i gang, så belaster vi ikke motoren ved at holde på den.

ret
		
;I den første runde skal der blot måles op, så her laver hall interruptet ikke andet end at
;måle "afstanden" og justerer hastigheden så accelerometeret får gode resultater.
Hall_Map_Lap:
		
		
call	Gyro_Kontrol
		ldi	R16, 1
		add	Length_L, R16
		ldi	R16, 0
		adc Length_H, R16

		ldi	R16, HIGH(Periode_m)	;Reference periode.
		lds	R17, Pulse_Time_H		;Indlæser den målte hastighed (periode)


		call	Hastigheds_kontrol


ret

Hall_Speed_Lap:									;Hvis den første omgang er færdig skal Hall interruptet stadig måle op
;										og justerer hastigheden. Den skal dog yderligere skifte mellem de målte banestykker


		cpi		Length_H,	0			;Først checkes om der er noget af Længden tilbage.
		brne	RUN
		cpi		Length_L, 	0
		brne	RUN
		ld		Length_L,	Y+			;Ellers indlæses det næste stykke
		ld		Length_H,	Y+			;Ellers indlæses det næste stykke
		ld		Type,		Y+			;
		
		
RUN:

		cpi		Type,		1			;check om lille højre
		breq	RUN_S1
		cpi		Type,		2			;check om lille venstre
		breq	RUN_S1
		cpi		Type,		3			;check om stor højre
		breq	RUN_S2
		cpi		Type,		4			;check om stor venstre
		breq	RUN_S2
										;Hvis alle check fejler må der være tale om et lige stykke

		lds		R17,	Pulse_Time_H		;Indlæser den målte hastighed (periode)
		ldi		R16,	high(Periode_l)			;Reference periode.;		lds		R17,	Pulse_Time_H		;Indlæser den målte hastighed (periode)
		
call	Hastigheds_kontrol

rjmp	RUN_DONE								;Hop til run_done når hastigheden er sat

RUN_S1:

		ldi		R16,	high(Periode_s1)			;Reference periode.
		lds		R17,	Pulse_Time_H		;Indlæser den målte hastighed (periode)
		
call	Hastigheds_kontrol

rjmp	RUN_DONE



RUN_S2:

		ldi		R16,	high(Periode_s2)			;Reference periode.
		lds		R17,	Pulse_Time_H		;Indlæser den målte hastighed (periode)
		
call	Hastigheds_kontrol

rjmp	RUN_DONE

RUN_DONE:
		subi		Length_L, 1					;Sætter den tilbageværende "Længde" ned med en.
		sbci		Length_H, 0
ret












