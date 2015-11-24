#include "DataLinkTransmit.h"


DataLinkTransmit::DataLinkTransmit()
{
	GENERATOR = 0x107 << 7;
	CHARS_IN_FRAME = 3;
}

DataLinkTransmit::~DataLinkTransmit()
{
}

void DataLinkTransmit::assembleFrame(vector<bool>& aPayload, int anIndex, int maxIndex) 
{
	payload.clear();	

	payload.push_back(0);
	payload.push_back(1); 
	payload.push_back(1); 
	payload.push_back(1); 
	payload.push_back(1); 
	payload.push_back(1); //Flag
	payload.push_back(1); 
	payload.push_back(0);
								
	//payload.push_back(anIndex);										//Sekvensnummer
	//payload.push_back(maxIndex);
	for (int i = 0; i < aPayload.size(); i++)
		payload.push_back(aPayload[i]);
	//generateCRC(payload);
	payload.push_back(126);
	payload.insert(payload.begin(), 32);//preamble indsættes til sidst
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

vector<bool> DataLinkTransmit::returnPayload()
{
	return payload;
}

void DataLinkTransmit::printFrames()
{
	for (unsigned int i = 0; i < payload.size(); i++)
		cout << payload[i] << endl;
}