#include "DataLinkTransmit.h"


DataLinkTransmit::DataLinkTransmit(void)
{
	chat = "";
	index = 0;
}

DataLinkTransmit::~DataLinkTransmit(void)
{
}

void DataLinkTransmit::assembleFrame(vector<int>& Payload, int anIndex, int maxIndex){
		myFrame.clear();
		myFrame.push_back(32);											//Preamble
		myFrame.push_back(126);											//Flag
		myFrame.push_back(anIndex);										//Sekvensnummer
		myFrame.push_back(maxIndex);
		if (Payload.size() % CHARS_IN_FRAME != 0 && Payload.size() - (anIndex*CHARS_IN_FRAME) < CHARS_IN_FRAME && anIndex <= maxIndex) //maxindex skal findes matematisk
		{
			for (int i = anIndex*CHARS_IN_FRAME; i < anIndex*CHARS_IN_FRAME + (Payload.size() % CHARS_IN_FRAME); i++)
			{
				myFrame.push_back(Payload[i]);
				generateCRC(myFrame);
				myFrame.push_back(126);
				printFrames();
			}
		}
			else if (anIndex > maxIndex)
			{
				cout << "index too large" << endl;
			}
			else
			{
				for (int i = anIndex*CHARS_IN_FRAME; i < (anIndex*CHARS_IN_FRAME + CHARS_IN_FRAME); i++)			//Tekst
				myFrame.push_back(Payload[i]);
				generateCRC(myFrame);			//CRC
				myFrame.push_back(126);										//Flag
				printFrames();
			}
											//placeholder for at sende DataLinkTransmit videre
		}

void DataLinkTransmit::checkCRC(vector<int>& iVector) {
	//opsætning af variable
	int iByte = 0;
	int Loop = 0;

	//Syndromet beregnes
	for (int i : iVector)
	{
		iByte = iByte | i;
		Loop = 0;
		while (Loop < 8)
		{
			bitset<16> s(iByte);
			if (s[15])
				iByte = iByte ^ GENERATOR;

			iByte = iByte << 1;
			Loop++;
		}
	}

	//Syndromet returneres
	cout << "Syndromet er: " << iByte << endl;
	iVector.pop_back();
}

void DataLinkTransmit::printText()
{
	cout << chat << endl;
}
	
void DataLinkTransmit::printFrames()
{
	for(unsigned int i = 0; i < myFrame.size(); i++)
		cout << myFrame[i] << endl;
}

void DataLinkTransmit::generateCRC(vector<int>& iVector)
{
	//opsætning
	iVector.push_back(0x00);
	int iByte = 0;
	int Loop = 0;
	
	//Syndromet beregnes
	for (int i : iVector)
	{
		iByte = iByte | i;
		Loop = 0;
		while (Loop < 8)
		{
			bitset<16> s(iByte);
			if (s[15])
				iByte = iByte ^ GENERATOR;

			iByte = iByte << 1;
			Loop++;
		}
	}

	//Syndrom tilføjes
	iByte = iByte >> 8;
	iVector.pop_back();
	iVector.push_back(iByte);
}