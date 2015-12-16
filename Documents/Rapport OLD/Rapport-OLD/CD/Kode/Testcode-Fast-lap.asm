;Main.asm

.org 0x0000
rjmp Init

;Interrupt vector mapping

;Library includes
.include "SRAM-Mapping.asm"
.include "Delays.asm"
.include "Motor_Control.asm"
.include "USART_Library.asm"
.include "I2C.asm"
.include "MPU-6050.inc"
.include "MPU-6050.asm"

Init:
	
	;Initialize the stack
	LDI	R16, low(RAMEND)
    OUT	SPL, R16
	LDI	R16, high(RAMEND)
    OUT	SPH, R16			

	USART_Init 0b00000000,0b00001000 
	Motor_Init
	I2C_Init 0x00,0x12	;Prescaler 4 and TWBR 12
	MPU6050_Init
	MPU6050_Init
	MPU6050_Init
	ldi R16, 'D'
	call USART_Transmit
	USART_Newline
	Motor_Set 120

	rjmp	Main

Main:

	.equ NUMB = 1000

	call MPU6050_Read_Dataset

	lds R17, GYRO_ZOUT_H

	lds R16, GYRO_ZOUT_L

	call USART_Decimal_S16

	USART_Newline


	lds R17, GYRO_ZOUT_H

	lds R16, GYRO_ZOUT_L

	sbrs R17, 7
	rjmp COMPUTE

	subi R16, 0x01
	sbci R17, 0x00
	com R16
	com R17

COMPUTE:

	cpi R17, HIGH(NUMB) ; 00011111 01000001 
	
	brlt LOWER

	;Higher

	cpi R17, HIGH(NUMB)
	breq LOWER_CHECK

	HIGHER:

	Motor_Set 100 ;100

	ldi R16, 'H'
	call USART_Transmit
	USART_Newline
	rjmp Main_End
	
	LOWER_CHECK:
	cpi R16, LOW(NUMB)
	brlo LOWER
	rjmp HIGHER

	LOWER:
		Motor_Set 180 ;185
		ldi R16, 'L'
		call USART_Transmit
		USART_Newline
		rjmp Main_End

Main_End:

rjmp	MAIN

