@echo off
REM Makefile for programming ATmega32 using assembler

REM For the little blue usbasp programmer
set PROGRAMMER=-c usbasp -P usb 
set HighFuse=0xd9
set LowFuse=0xFF


@echo on

avrdude -p m32 %PROGRAMMER% -U hfuse:w:%HighFuse%:m -U lfuse:w:%LowFuse%:m

pause

	
	

	
	
