#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
static const int CHARS_IN_FRAME = 3;
static const int GENERATOR = 0x107 << 7;
class DataLinkTransmit
{
public:
	DataLinkTransmit(void);							//instancieres
	~DataLinkTransmit(void);    
	void assembleFrame(vector<int>& Payload, int anIndex, int maxIndex);
	void generateCRC(vector<int>&);
	//	void bitStuffing();

	void checkCRC(vector<int>&);
	void printText();
	void printFrames();

protected:
	int index;
	string chat;
	vector<int> myFrame;
	//Preamble – 01111110 (flag) – Adresse – Sekvensnummer (1byte)  - L (længden minus preamble)  -  Data - Trailer (CRC 1 byte) - 01111110 (flag)
};