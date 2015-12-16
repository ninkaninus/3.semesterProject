@echo off
REM Makefile for programming ATmega32 using assembler

REM For the little blue usbasp programmer
set PROGRAMMER=-c usbasp -P usb 

@echo on

avrdude -p m32 %PROGRAMMER% -e

pause

	
	

	
	
