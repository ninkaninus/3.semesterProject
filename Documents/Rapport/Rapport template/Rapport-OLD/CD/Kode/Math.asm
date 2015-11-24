Sum_16:
	add R16, R18
	adc R17, R19
ret

Div16_8:
	
	clr ZH ;Kvotient high
	clr ZL ;Kvotient low

Div16_8_Loop:

	adiw ZH:ZL, 1 ;Kvotient ++

	sub R16 ,R18 ;Tr�k n�vner fra t�ller
	sbci R17, 0
	brcc Div16_8_Loop
	
	sbiw ZH:ZL, 1 ;Kvotient --

	add R16, R18 ;L�g n�vner til
	
	mov R18, R16
	movw R17:R16,ZH:ZL

ret
