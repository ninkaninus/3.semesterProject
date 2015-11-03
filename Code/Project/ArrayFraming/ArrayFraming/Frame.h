#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Frame
{
public:
	Frame(void);
	~Frame(void);    
	Frame(string enC);
	void printText();
	void printFrames();

protected:
	string chat;
	vector<int> myFrame;
	//Preamble – 01111110 (flag) – Adresse – Sekvensnummer (1byte)  - L (længden minus preamble)  -  Data - Trailer (CRC 1 byte) - 01111110 (flag)
};