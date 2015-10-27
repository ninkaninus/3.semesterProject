;Author: Jonas A. L. Andersen

;Requires the Timer library made by Kristian! And the SRAM-Mapping.asm
;These macros are intended for a micro running 16MHZ

;This macro can generate from 1 to 255 ms of delay.  
;Uses R16, R17 and R18
.MACRO	DELAY_MS_M					; Cycles to execute 
	LDI R16, @0 ;					; 1 cycle to execute
	DELAY_MS_M_2: ;-----------------/
	LDI R17, 15 ;	              /
	DELAY_MS_M_1:	;------------/    /
	LDI R18, 177;		     /    /
	DELAY_MS_M_0: ;-------/    /    /
	NOP ;			    /C   /B   /A
	NOP ;				/	 /	  /
	NOP ;				/	 /	  /
	DEC R18 ;		    /    /    /
	BRNE DELAY_MS_M_0 ;---/    /    /
	DEC R17 ;		         /    /
	NOP ;					 /	  /
	BRNE DELAY_MS_M_1 ;--------/    /
	DEC R16 ;		              /
	NOP ;						  /
	NOP ;						  /
	NOP ;						  /
	NOP ;						  /
	NOP ;						  /
	NOP ;						  /
	BRNE DELAY_MS_M_2 ;-------------/
.ENDMACRO
; Block C: 177*(1+1+1+1+2)-1 = 1061
; Block B: 15*(1+C+1+1+2)-1 = 15990 
; Block A: x*(1+B+1+1+1+1+1+1+1+2)-1 = x*16000-1
; Total # of cycles is: 1 + A = x*16000 
; Formula for delay: x*1ms

Delay_MS:
	mov R9, R16
	lds R3, Timer_1ms_L
	lds R4, Timer_1ms_M
	lds R5, Timer_1ms_H

Delay_MS_Loop:
	
	sei
	lds R6, Timer_1ms_L
	lds R7, Timer_1ms_M
	lds R8, Timer_1ms_H

	cli
	sub R6, R3
	sbc R7, R4
	sbc R8, R5

	cp R6, R9

	brlo Delay_MS_Loop
	sei
ret