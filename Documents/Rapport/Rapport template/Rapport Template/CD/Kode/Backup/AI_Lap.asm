; AI_Lap_Preround = 0
; AI_Lap_Mapping = 1
; AI_Lap_Speed = 2

AI_Lap_Interrupt:						;Lap interrupt skifter fra initial runden til den første runde til alle resterende.

		lds		R20, AI_Check_Lap		

		;Were we running a speed lap when we hit the line. Then go to speed lap handling.
		cpi		R20, AI_Lap_Speed
		brsh	AI_Test_Speed_Lap
		
		;Were we running a mapping lap when we hit the line. Then go to the first speed lap handling.
		cpi		R20, AI_Lap_Mapping
		brsh	AI_Test_Speed_Lap_First

		;We were in preround when we hit the line. So initialize the mapping round.
		ldi		R20, AI_Lap_Mapping
		sts		AI_Check_Lap, R20

		ldi		Type,		0
		ldi		Length_L,	0
		ldi		Length_H,	0

		ret			

AI_Test_Speed_Lap_First:
		;Sørger for at gemme det sidste banestykke. Da stykkerne bliver gemt ved skift til næste stykke.

		ldi R20, 5
		add		Length_L, R20			;Forøg antal med fem - Bruges til at sikre at den ikke løber tør i slutningen. Antal kan ændres.
		ldi		R16, 0
		adc		Length_H, R16

		st		Y+,			Length_L
		st		Y+,			Length_H	;Sæt Længden ind først-
		st		Y+,			Type		;og derefter vejtypen.


;Vi har ikke afprøvet dette, så det kigger vi på senere.


AI_Test_Speed_Lap:
		
		ldi		R20, 2
		sts     AI_Check_Lap, R20

;		lds		R20,		AI_Hastighed_D
;		inc		R20
;		sts		AI_Hastighed_D,R20

		ldi		YL, low(Map_Start)
		ldi		YH, high(Map_Start)
		ld		Length_L,	Y+			;Indlæser den første del af af det gemte map.
		ld		Length_H, 	Y+
		ld		Type,		Y+

;Vi har ikke afprøvet dette, så det kigger vi på senere.
		ret
















