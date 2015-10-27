.EQU	MOTOR_PIN = PD7						;The pin that the motor is connected to
.EQU	BRAKE_PIN = PB0

.MACRO Motor_Init
	in R16, DDRD							;Load in the current setup of the portb
	ori R16, (1<<PD7)						;OR in the setup that we wish to have
	out DDRD, R16

	ldi R16, 0b01101001						;Fast-pwm, non-inverting mode, no prescaling
	out TCCR2, R16							;
.ENDMACRO

; Use desired braking time in MS as argument
.MACRO Brake_MS
		
.ENDMACRO

Motor_Set: 
	out OCR2, R16							;Set the duty cycle of the motor
ret

.MACRO Brake_Init

	in R16, DDRB							;Load in the current setup of the portc
	ori R16, (1<<BRAKE_PIN)					;OR in the setup that we wish to have
	out DDRB, R16							;Set brake pin as output
	
	cbi	PORTB, BRAKE_PIN					;Set brake to high state

.ENDMACRO

Motor_Set_Percentage:
	cpi R16, 101							;Check if the number is within the percentage range of 100
	brsh Motor_Set_Percentage_End			;Branch if not

	ldi R17, 255							;Using the formula (N*255)/100=N% of 255
	mul R16, R17							;Multiply the number by 255

	mov R16, R0								;The multiplication hardware leaves the result in R1:R0
	mov R17, R1								;

	ldi R18, 100							;Load in the 100 to divide with
	call Div16_8							;Divide with 100, the rest is returned in R18

	cpi R18, 50								;Check to see if we should round of or down.
	brlo Motor_Set_Percentage_Out			;R16 is actually the trunctuated value of the divison which is the same as rounding down.
	inc R16									;Increment if we were rounding up

Motor_Set_Percentage_Out:

	call Motor_Set							;Set the duty cycle of the motor pwn as the % of 255

Motor_Set_Percentage_End:
 ret
