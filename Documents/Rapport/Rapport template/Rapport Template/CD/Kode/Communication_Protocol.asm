.Macro Comm_Init
	ldi R16, 0x01							;Initialize the counter as being the first byte
	sts Comm_Received_Byte_Num, R16			;
	clr R16									;Clear all of the SRAM-values used
	sts Comm_Received_Byte_1, R16			;
	sts Comm_Received_Byte_2, R16			;
	sts Comm_Received_Byte_3, R16			;
.ENDMACRO


;Define Types
.equ Comm_Type_Set = 0x55					;Used for setting a value or activating a command
.equ Comm_Type_Get = 0xAA					;Used for getting a value from the microcontroller

;Define Set Commands
.equ Comm_Command_Start = 0x10				;Start the car at a specific % of motor speed
.equ Comm_Command_Stop = 0x11				;Stop the car

.equ Comm_Command_Speed_H = 0x12
.equ Comm_Command_Speed_L = 0x13

;Define Get Commands
.equ Comm_Command_Xaccel_H = 0xA1
.equ Comm_Command_Xaccel_L = 0xA2

.equ Comm_Command_Zgyro_H = 0xA3
.equ Comm_Command_ZGyro_L = 0xA4

.equ Comm_Command_Ticks_H = 0xA5
.equ Comm_Command_Ticks_L = 0xA6

.equ Comm_Command_LapTime_H = 0xA7
.equ Comm_Command_LapTime_L = 0xA8

.equ Comm_Command_LapTicks_H = 0xA9
.equ Comm_Command_LapTicks_L = 0xAA

.equ Comm_Command_Data = 0xAB

;---------------------------------------------------------------------------------------------------------------------
;Comm Received: Used as a USART Received interrupt
;---------------------------------------------------------------------------------------------------------------------
Comm_Received:

	lds R16, Comm_Received_Byte_Num			;What byte # did we receive

	cpi R16, 0x01							;If it was the first
	breq Comm_Received_Type					;Set the type

	cpi R16, 0x02							;If it was the second
	breq Comm_Received_Command				;Set the command

	;Working under the assumption that if it was not the first or second byte, then it must be the third.

	rjmp Comm_Received_Execute				;Go to the execution of the received telegram


;---------------------------------------------------------------------------------------------------------------------
;Received a type
;---------------------------------------------------------------------------------------------------------------------
Comm_Received_Type:
	
	in R16, UDR	
				
Comm_Received_Type_Set_Check:				;Check if we received a set type
	cpi R16, Comm_Type_Set					;Check for set type
	breq Comm_Received_Type_Valid			;Branch to the next check if not the case

Comm_Received_Type_Get_Check:				;Check if we received a get type
	cpi R16, Comm_Type_Get					;Check for get type
	breq Comm_Received_Type_Valid			;Branch to the reset since we did not received a valid type

Comm_Received_Type_Reset:					;Branch here if it was not a valid type
	reti									;Does nothing else than return since the byte counter is already at one

Comm_Received_Type_Valid:
	sts Comm_Received_Byte_1, R16			;Store the received type in SRAM	
	ldi R16, 0x02							;Set the counter to two
	sts Comm_Received_Byte_Num, R16			;Store it					
reti										;Return from interrupt

;---------------------------------------------------------------------------------------------------------------------
;Received a command
;---------------------------------------------------------------------------------------------------------------------
Comm_Received_Command:

	lds R16, Comm_Received_Byte_1

Comm_Received_Command_Type_Set_Check:				;Check if we received a set type
	cpi R16, Comm_Type_Set							;Check for set type
	breq Comm_Received_Command_Type_Set				;Branch to the next check if not the case

Comm_Received_Command_Type_Get_Check:				;Check if we received a get type
	cpi R16, Comm_Type_Get							;Check for get type
	breq Comm_Received_Command_Type_Get				;Branch to the reset since we did not received a valid type

Comm_Received_Command_Failure:						;This should never actually be called, since this is only possible if something else is tangling with the specific SRAM address inbetween bytes
	ldi R16, 'C'											;But in the case that this happens
	call USART_Transmit								;The program will be stuck in the interrupt and spam
	rjmp Comm_Received_Command_Failure				;'C' over the USART

;---------------------------------------------------------------------------------------------------------------------
;Check for matching set commands
;---------------------------------------------------------------------------------------------------------------------
Comm_Received_Command_Type_Set:
	in R16, UDR	

;Start			
Comm_Received_Command_Start_Check:					;Check if we received a start command
	cpi R16, Comm_Command_Start						;Check for start command
	breq Comm_Received_Command_Valid				;Branch to the next check if not the case

;Stop
Comm_Received_Command_Stop_Check:					;Check if we received a stop command
	cpi R16, Comm_Command_Stop						;Check for stop command
	breq Comm_Received_Command_Valid				;Branch to the next check if not the case

;Speed_H
Comm_Received_Command_Speed_H_Check:				;Check if we received a stop command
	cpi R16, Comm_Command_Speed_H					;Check for stop command
	breq Comm_Received_Command_Valid				;Branch to the next check if not the case

;Speed_L
Comm_Received_Command_Speed_L_Check:				;Check if we received a stop command
	cpi R16, Comm_Command_Speed_L					;Check for stop command
	breq Comm_Received_Command_Valid				;Branch to the next check if not the case

;Invalid
	jmp Comm_Received_Command_Reset					;If we did not in fact receive a valid set command, then reset

;---------------------------------------------------------------------------------------------------------------------
;Check for matching get commands
;---------------------------------------------------------------------------------------------------------------------
Comm_Received_Command_Type_Get:
	in R16, UDR	

;Laptime
Comm_Received_Command_Data_Check:					;Check if we received a LapTime command
	cpi R16, Comm_Command_Data						;Check for LapTime command
	breq Comm_Received_Command_Valid				;Branch to the next check if not the case

;Invalid
	jmp Comm_Received_Command_Reset					;If we did not in fact receive a valid set command, then reset

;---------------------------------------------------------------------------------------------------------------------
;Command handling
;---------------------------------------------------------------------------------------------------------------------
Comm_Received_Command_Reset:
	ldi R16, 0x01									;Reset the byte counter since we received an invalid command after a valid type									
	sts Comm_Received_Byte_Num, R16					;
	reti											;Return

Comm_Received_Command_Valid:						
	sts Comm_Received_Byte_2, R16					;Store the received type in SRAM	
	ldi R16, 0x03									;Set the counter to two
	sts Comm_Received_Byte_Num, R16					;Store it		
				
reti												;Return from interrupt


;---------------------------------------------------------------------------------------------------------------------
;Execute
;---------------------------------------------------------------------------------------------------------------------
Comm_Received_Execute:

	in r16, UDR								;Read in the received parameter
	sts Comm_Received_Byte_3, R16			;Store it in SRAM
	
	ldi R16, 0x01							;Reset the counter
	sts Comm_Received_Byte_Num, R16			;Store it in SRAM

;---------------------------------------------------------------------------------------------------------------------
;Execute Types
;---------------------------------------------------------------------------------------------------------------------

	lds R16, Comm_Received_Byte_1			;Load in the first(Type) byte

	;SET
	cpi R16, Comm_Type_Set					;Check if we received a SET and branch if it was
	breq Comm_Received_Execute_Set			;

	;GET
	cpi R16, Comm_Type_Get					;Check if we received a GET and branch if it was
	breq Comm_Received_Execute_Get			;

	reti
;---------------------------------------------------------------------------------------------------------------------
;Execute SET's
;---------------------------------------------------------------------------------------------------------------------

Comm_Received_Execute_Set:

	lds R16, Comm_Received_Byte_2			;Load in the second(Command) byte

	cpi R16, Comm_Command_Start				;Check if we received a Start command
	breq Comm_Received_Execute_Set_Start	;

	cpi R16, Comm_Command_Stop				;Check if we received a Stop command
	breq Comm_Received_Execute_Set_Stop		;

	cpi R16, Comm_Command_Speed_H
	breq Comm_Received_Execute_Speed_H

	cpi R16, Comm_Command_Speed_L
	breq Comm_Received_Execute_Speed_L

	;Insert error handling here

	reti									;Do nothing if it was not a legit code

;Start
Comm_Received_Execute_Set_Start:

	lds R16, Comm_Received_Byte_3			;Load in the third(Parameter) byte

	call Motor_Set_Percentage

Comm_Received_Execute_Set_Start_End:

	reti									;Return from interrupt

;Stop
Comm_Received_Execute_Set_Stop:
	
	ldi R16, 'S'
	call USART_Transmit

	ldi R16, 0x00							;Load in 0x00
	out OCR2, R16							;And set the pwm duty cycle to nothing to stop the motor.

	reti

Comm_Received_Execute_Speed_H:
	lds R16, Comm_Received_Byte_3
	sts	Temp, R16 

	reti

Comm_Received_Execute_Speed_L:
	lds R16, Temp
	sts Speed_H, R16 
	lds R16, Comm_Received_Byte_3
	sts Speed_L, R16 

	reti

;---------------------------------------------------------------------------------------------------------------------
;Execute GET's
;---------------------------------------------------------------------------------------------------------------------

Comm_Received_Execute_Get:	

	lds R16, Comm_Received_Byte_2			;Load in the second(Command) byte

	cpi R16, Comm_Command_Data		
	breq Comm_Received_Execute_Get_Data		

	;Insert error handling here

	reti									;Do nothing if it was not a legit code

Comm_Received_Execute_Get_Data:
	call Comm_Received_Execute_Get_Ticks
	;call Comm_Received_Execute_Get_Zgyro
	;call Comm_Received_Execute_Get_Xaccel
	reti

Comm_Received_Execute_Get_Xaccel:

	call MPU6050_Read_Accel_X

	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_Xaccel_H
	call USART_Transmit

	lds R16, ACCEL_XOUT_H
	call USART_Transmit
	
	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_Xaccel_L
	call USART_Transmit

	lds R16, ACCEL_XOUT_L
	call USART_Transmit

	ret

Comm_Received_Execute_Get_Zgyro:
	call MPU6050_Read_Gyro_Z

	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_Zgyro_H
	call USART_Transmit

	lds R16, GYRO_ZOUT_H
	call USART_Transmit
	
	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_Zgyro_L
	call USART_Transmit

	lds R16, GYRO_ZOUT_L
	call USART_Transmit

	ret

Comm_Received_Execute_Get_Ticks:

	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_Ticks_H
	call USART_Transmit

	lds R16, Ticks_H
	call USART_Transmit
	
	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_Ticks_L
	call USART_Transmit

	lds R16, Ticks_L
	call USART_Transmit

	ret

;---------------------------------------------------------------------------------------------------------------------
;Send
;---------------------------------------------------------------------------------------------------------------------

;LapTime
Comm_Send_LapTime:
	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_LapTime_H
	call USART_Transmit

	lds R16, Lap_time_M
	call USART_Transmit
	
	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_LapTime_L
	call USART_Transmit

	lds R16, Lap_time_L
	call USART_Transmit

	ret

;Lap ticks
Comm_Send_LapTicks:
	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_LapTicks_H
	call USART_Transmit

	lds R16, Ticks_Lap_H
	call USART_Transmit
	
	ldi R16, 0xBB
	call USART_Transmit

	ldi R16, Comm_Command_LapTicks_L
	call USART_Transmit

	lds R16, Ticks_Lap_L
	call USART_Transmit

	ret
