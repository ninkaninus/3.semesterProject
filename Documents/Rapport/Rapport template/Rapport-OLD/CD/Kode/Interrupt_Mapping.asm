;Interrupt vector mapping
.org 0x00
rjmp Init
;External interrupt1
;.org 0x04
;jmp	Input_Capture
;Timer1 Input Capture interrupt
.org	0x0C
jmp	Input_Capture
;Timer0 CTC interrupt
.org 0x14
jmp Timer0_Update
;USART received interrupt
.org 0x1A
jmp Comm_Received
;Comparator interrupt
.org 0x24
jmp Lap_Time
