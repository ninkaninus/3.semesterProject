.MACRO Setup
	;Initialize the stack
	LDI	R16, low(RAMEND)
    OUT	SPL, R16
	LDI	R16, high(RAMEND)
    OUT	SPH, R16			

	USART_Init 0b00000000,0b01100111	;Initialize the USART module with 9600 baud @ 16MHz clock
	Comm_Init							;Intialize the communication protocol
	Motor_Init							;Initialize the motor pwm
	Brake_Init							;Initialize the brake pin
	I2C_Init 0x00,0x12					;Initialize the TWI module with Prescaler 4 and TWBR 12
	Time_Init							;Initialize the timer associated with timekeeping
	WheelSpeed_Init						;Initialize the wheel speed sensor
	LapCounter_Init						;Initialize the lap counter
	MPU6050_Init						;Initialize the MPU6050 3 times to make sure it writes the values(We should make some kind of check instead)
	MPU6050_Init						;
	MPU6050_Init						;
	AI_Init
.ENDMACRO
