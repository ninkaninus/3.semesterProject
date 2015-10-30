#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
static const int CHARS_IN_DataLinkTransmit = 3;
class DataLinkTransmit
{
public:
	DataLinkTransmit(void);
	~DataLinkTransmit(void);    
	DataLinkTransmit(string enC);
	DataLinkTransmit(string enC, int etIndex);
	void printText();
	void printDataLinkTransmits();

protected:
	int index;
	string chat;
	vector<int> myFrame;
	//Preamble – 01111110 (flag) – Adresse – Sekvensnummer (1byte)  - L (længden minus preamble)  -  Data - Trailer (CRC 1 byte) - 01111110 (flag)
};