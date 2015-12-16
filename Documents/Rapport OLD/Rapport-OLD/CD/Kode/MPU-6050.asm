;This library is for the 6DOF MPU-6050 from invensense.
;This library relies on the I2C library made by StjerneIdioten.
;This library relies on the "MPU-6050.inc" where all the definitions of registers are defined.
;This library relies on having defined the correct SRAM locations prior to reading in data.

;Setup the MPU-6050
.MACRO MPU6050_Init

	call I2C_Start							;Send a start									
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050

	I2C_Write MPU6050_RA_SMPLRT_DIV			;Write the address to start the burst write at

	;Sets sample rate to 8000/1+7 = 1000Hz
	I2C_Write 0x07

	;MPU6050_RA_CONFIG, Disable FSync, 256Hz DLPF
	I2C_Write 0x00

	;MPU6050_RA_GYRO_CONFIG, Disable gyro self tests, scale of 500 degrees/s
	I2C_Write 0b00001000

	;MPU6050_RA_ACCEL_CONFIG ,Disable accel self tests, scale of +-16g, no DHPF
	I2C_Write 0b00001000

	;MPU6050_RA_FF_THR ,Freefall threshold of |0mg|
	I2C_Write 0x00

	;MPU6050_RA_FF_DUR ,Freefall duration limit of 0
	I2C_Write 0x00

	;MPU6050_RA_MOT_THR ,Motion threshold of 0mg
	I2C_Write 0x00

	;MPU6050_RA_MOT_DUR ,Motion duration of 0s
	I2C_Write 0x00

	;MPU6050_RA_ZRMOT_THR ,Zero motion threshold
	I2C_Write 0x00

	;MPU6050_RA_ZRMOT_DUR ,Zero motion duration threshold
	I2C_Write 0x00

	;MPU6050_RA_FIFO_EN ,Disable sensor output to FIFO buffer
	I2C_Write 0x00

	;Aux I2C setup
	;MPU6050_RA_I2C_MST_CTRL, Sets AUX I2C to single master control, plus other config
	I2C_Write 0x00

	;Setup AUX I2C slaves
	;MPU6050_RA_I2C_SLV0_ADDR
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV0_REG
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV0_CTR
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV1_ADDR
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV1_REG
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV1_CTRL
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV2_ADDR
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV2_REG
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV2_CTRL
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV3_ADDR
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV3_REG
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV3_CTRL
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV4_ADDR
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV4_REG
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV4_DO
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV4_CTRL
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV4_DI
	I2C_Write 0x00

	;MPU6050_RA_I2C_MST_STATUS ;Read-only

	;MPU6050_RA_INT_PIN_CFG, Setup INT pin and AUX I2C pass through
	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050

	I2C_Write MPU6050_RA_INT_PIN_CFG		;Write the address to start the burst write at
	I2C_Write 0x00							;Clear the register and burst write

	;MPU6050_RA_INT_ENABLE, Enable data ready interrupt
    I2C_Write 0x00

	;MPU6050_RA_DMP_INT_STATUS				;Read-only
    ;MPU6050_RA_INT_STATUS 3A				;Read-only
    ;MPU6050_RA_ACCEL_XOUT_H				;Read-only
    ;MPU6050_RA_ACCEL_XOUT_L				;Read-only
    ;MPU6050_RA_ACCEL_YOUT_H				;Read-only
    ;MPU6050_RA_ACCEL_YOUT_L				;Read-only
    ;MPU6050_RA_ACCEL_ZOUT_H				;Read-only
    ;MPU6050_RA_ACCEL_ZOUT_L				;Read-only
    ;MPU6050_RA_TEMP_OUT_H					;Read-only
    ;MPU6050_RA_TEMP_OUT_L					;Read-only
    ;MPU6050_RA_GYRO_XOUT_H					;Read-only
    ;MPU6050_RA_GYRO_XOUT_L					;Read-only
    ;MPU6050_RA_GYRO_YOUT_H					;Read-only
    ;MPU6050_RA_GYRO_YOUT_L					;Read-only
    ;MPU6050_RA_GYRO_ZOUT_H					;Read-only
    ;MPU6050_RA_GYRO_ZOUT_L					;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_00			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_01			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_02			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_03			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_04			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_05			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_06			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_07			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_08			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_09			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_10			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_11			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_12			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_13			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_14			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_15			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_16			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_17			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_18			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_19			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_20			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_21			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_22			;Read-only
    ;MPU6050_RA_EXT_SENS_DATA_23			;Read-only
    ;MPU6050_RA_MOT_DETECT_STATUS			;Read-only

	;Slave out, dont care

	;MPU6050_RA_I2C_SLV0_DO
	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050

	I2C_Write MPU6050_RA_I2C_SLV0_DO		;Write the address to start the burst write at
	I2C_Write 0x00							;Clear the register and burst write

	;MPU6050_RA_I2C_SLV1_DO
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV2_DO
	I2C_Write 0x00

	;MPU6050_RA_I2C_SLV3_DO
	I2C_Write 0x00

	;MPU6050_RA_I2C_MST_DELAY_CTRL, More slave config
	I2C_Write 0x00

	;MPU6050_RA_SIGNAL_PATH_RESET, Reset sensor signal paths
	I2C_Write 0x00

	;MPU6050_RA_MOT_DETECT_CTRL, Motion detection control
	I2C_Write 0x00

	;MPU6050_RA_USER_CTRL, Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
	I2C_Write 0x00

	;MPU6050_RA_PWR_MGMT_1, Sets clock source to gyro reference w/ PLL
	I2C_Write 0b00000010

	;MPU6050_RA_PWR_MGMT_2, Controls frequency of wakeups in accel low power mode plus the sensor standby modes
	I2C_Write 0x00

	;MPU6050_RA_BANK_SEL					;Not in datasheet
    ;MPU6050_RA_MEM_START_ADDR				;Not in datasheet
    ;MPU6050_RA_MEM_R_W						;Not in datasheet
    ;MPU6050_RA_DMP_CFG_1					;Not in datasheet
    ;MPU6050_RA_DMP_CFG_2					;Not in datasheet
    ;MPU6050_RA_FIFO_COUNTH					;Read-only
    ;MPU6050_RA_FIFO_COUNTL					;Read-only

    ;Data transfer to and from the FIFO buffer
	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050

	I2C_Write MPU6050_RA_FIFO_R_W			;Write the address of the FIFO buffer register
	I2C_Write 0x00							;Write zero to disable it.

	;MPU6050_RA_WHO_AM_I					;Read-only, I2C address

	call I2C_Stop							;Send a stop
.ENDMACRO


;This macro gets the value stored in the Who_Am_I register in the MPU-6050. This will always return 0x68 independent of AD0! Useful for testing the connection.
.MACRO MPU6050_Get_Address
	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050
	I2C_Write MPU6050_RA_WHO_AM_I			;Write the address of the Who Am I register

	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_R				;Send the read address of the MPU6050

	I2C_Read I2C_Nack						;Move the read in value to R17, because R16 is used in the stop function
	mov R17, R16							;

	call I2C_Stop							;Send a stop

	mov R16, R17							;Move the read in value back into R16 
.ENDMACRO


;Reads in the entire dataset supplied by the MPU6050 by doing a couple of burst reads. The values can be found at the SRAM addresses specified in SRAM-Mapping
MPU6050_Read_Dataset:
	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050
	I2C_Write MPU6050_RA_ACCEL_XOUT_H		;Write the address to begin reading from.

	call I2C_Start							;Send a repeated start
	I2C_Write MPU6050_ADDRESS_R				;Send the read address of the MPU6050

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_XOUT_H, R16					;Store the ACCEL_XOUT_H in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_XOUT_L, R16					;Store the ACCEL_XOUT_L in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_YOUT_H, R16					;Store the ACCEL_YOUT_H in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_YOUT_L, R16					;Store the ACCEL_YOUT_L in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_ZOUT_H, R16					;Store the ACCEL_ZOUT_H in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_ZOUT_L, R16					;Store the ACCEL_ZOUT_L in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts TEMP_OUT_H, R16						;Store the TEMP_OUT_H in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts TEMP_OUT_L, R16						;Store the TEMP_OUT_L in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts GYRO_XOUT_H, R16					;Store the GYRO_XOUT_H in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts GYRO_XOUT_L, R16					;Store the GYRO_XOUT_L in SRAM

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts GYRO_YOUT_H, R16					;Store the GYRO_YOUT_H in SRAM
	
	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts GYRO_YOUT_L, R16					;Store the GYRO_YOUT_L in SRAM
	
	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts GYRO_ZOUT_H, R16					;Store the GYRO_ZOUT_H in SRAM
	
	I2C_Read I2C_Nack						;Reply with an NACK to indicate that we do not wish to read the next byte too
	sts GYRO_ZOUT_L, R16					;Store the GYRO_ZOUT_L in SRAM
	call I2C_Stop							;Send a stop
ret											;Return

;Reads in the entire dataset supplied by the MPU6050 by doing a couple of burst reads. The values can be found at the SRAM addresses specified in SRAM-Mapping
MPU6050_Read_Gyro_Z:
	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050
	I2C_Write MPU6050_RA_GYRO_ZOUT_H		;Write the address to begin reading from.

	call I2C_Start							;Send a repeated start
	I2C_Write MPU6050_ADDRESS_R				;Send the read address of the MPU6050

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts GYRO_ZOUT_H, R16					;Store the GYRO_ZOUT_H in SRAM
	
	I2C_Read I2C_Nack						;Reply with an NACK to indicate that we do not wish to read the next byte too
	sts GYRO_YOUT_L, R16					;Store the GYRO_YOUT_L in SRAM

	call I2C_Stop							;Send a stop
ret											;Return

MPU6050_Read_Accel_X:
	call I2C_Start							;Send a start
	I2C_Write MPU6050_ADDRESS_W				;Send the write address of the MPU6050
	I2C_Write MPU6050_RA_ACCEL_XOUT_H		;Write the address to begin reading from.

	call I2C_Start							;Send a repeated start
	I2C_Write MPU6050_ADDRESS_R				;Send the read address of the MPU6050

	I2C_Read I2C_Ack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_XOUT_H, R16					;Store the ACCEL_XOUT_H in SRAM

	I2C_Read I2C_Nack						;Reply with an ACK to indicate that we wish to read the next byte too
	sts ACCEL_XOUT_L, R16					;Store the ACCEL_XOUT_L in SRAM

	call I2C_Stop							;Send a stop
ret											;Return


