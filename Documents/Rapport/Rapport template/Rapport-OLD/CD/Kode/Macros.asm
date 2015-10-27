.MACRO Push_Register_5
	push	@0
	push	@1
	push	@2
	push	@3
	push	@4
	in	R16, SREG
	push	R16
.ENDMACRO

.MACRO Pop_Register_5
	pop	R16
	out	SREG, R16
	pop	@0
	pop	@1
	pop	@2
	pop	@3
	pop	@4	
.ENDMACRO

.MACRO Push_Register_7
	push	@0
	push	@1
	push	@2
	push	@3
	push	@4
	push	@5
	push	@6
	in	R16, SREG
	push	R16
.ENDMACRO

.MACRO Pop_Register_7
	pop	R16
	out	SREG, R16
	pop	@0
	pop	@1
	pop	@2
	pop	@3
	pop	@4
	pop	@5
	pop	@6	
.ENDMACRO

.MACRO Set_SREG_1 
			lds		R16, SREG_1
			sbr		R16, (1<<@0)					; set bit in R16 (performs a logical ORI instruction)
			sts		SREG_1, R16
.ENDMACRO

.MACRO Clear_SREG_1 
			lds		R16, SREG_1
			cbr		R16, (1<<@0)					; clear bit in R16 (performs logical AND with complement of operand)
			sts		SREG_1, R16
.ENDMACRO
