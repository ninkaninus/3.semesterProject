#include "DataLinkTransmit.h"
#include <iostream>
#include <fstream>


DataLinkTransmit::DataLinkTransmit()
{
	GENERATOR = 0x107 << 7;
	CHARS_IN_FRAME = 100;
}

DataLinkTransmit::~DataLinkTransmit()
{
}

void DataLinkTransmit::transmitFrame(vector<bool>& aPayload, int anIndex, int maxIndex) 
{
	payload.clear();	
	vector<bool> bitStuffVector;									// Separat vector til data som skal bitstuffes

	//Start flag in binary
	payload.push_back(0);
	payload.push_back(1); 
	payload.push_back(1); 
	payload.push_back(1); 
	payload.push_back(1); 
	payload.push_back(1);											
	payload.push_back(1);	
	payload.push_back(0);
								
	for (int j = 7; j >= 0; j--)
	{
		bitset<8> indexBits(anIndex);								// Index tilføjes i binær
		bitStuffVector.push_back(indexBits[j]);
	}


	for (int j = 7; j >= 0; j--)
	{
		bitset<8> maxIndexBits(maxIndex);							// MaxIndex tilføjes i binær
		bitStuffVector.push_back(maxIndexBits[j]);
	}

	for (int i = 0; i < aPayload.size(); i++)						// Payload tilføjes
		bitStuffVector.push_back(aPayload[i]);


	int crcType = 32;												// CRC og bitstuffing
	generateCRC(bitStuffVector, crcType);
	bitStuffing(bitStuffVector);

	for (bool i : bitStuffVector)									// Alt smides til bage i framen
		payload.push_back(i);

	bitStuffVector.clear();

	payload.push_back(0);
	payload.push_back(1);
	payload.push_back(1);
	payload.push_back(1);
	payload.push_back(1);
	payload.push_back(1);											// Stop flag
	payload.push_back(1);
	payload.push_back(0);
	
	while (payload.size() % 4 != 0)									// Der tilføjes 0'er til antallet af bits går op i 4
	{
		payload.push_back(0);
	}

	/*
	//Debugging code to output the binary format of a data package
	ofstream out;

	out.open("test.txt");

	out << "1, 0, 1, 0, 0, 1, 1, 0, ";

	for (bool b : payload) out << b << ", ";

	out.close();
	*/

	transmitter.transmit(payload);
}

void DataLinkTransmit::generateCRC(vector<bool>& bVector, int& n)
{
	//Valg af generatorpolynomium
	double GENERATOR = 0;

	switch (n)
	{
	case 8:
		GENERATOR = 0b100000111;
		break;
	case 10:
		GENERATOR = 0b11000110101;
		break;
	case 16:
		GENERATOR = 0b10001000000100001;
		break;
	case 32:
		GENERATOR = 0b100000100110000010001110110110111;
		break;
	default:
		cout << "Fejl CRC ugyldigt skal vaere 8, 10, 16 eller 32 " << endl << n << " blev brugt, der erstattes med " << 8 << endl;
		GENERATOR = 0b100000111;
		n = 8;
	}


	bitset<33> G(GENERATOR);

	//opsætning
	vector<bool> CRC;
	for (bool i : bVector)
		CRC.push_back(i);
	for (int i = 0; i < n; i++)
		CRC.push_back(0);


	//Syndromet beregnes
	for (unsigned int i = 0; i < CRC.size() - n; i++)
	{
		if (CRC[i]) {
			// der er 1 - XOR

			for (int GEN = 0; GEN < n + 1; GEN++)
			{
				CRC[i + GEN] = CRC[i + GEN] ^ G[n - GEN];
			}
			//print(CRC, "test");
		}
	}

	//Syndrom tilføjes
	//cout << "CRC er: ";
	for (unsigned int i = CRC.size() - n; i < CRC.size(); i++) {
		bVector.push_back(CRC[i]);
		//cout << CRC[i];
	}
}

void DataLinkTransmit::bitStuffing(vector<bool>& bVector)
{
	//opsætning af variable
	vector<bool> stuff;
	int loop = 0;

	//Stuffing
	for (bool i : bVector)
	{
		stuff.push_back(i);
		if (i) {
			//1
			loop++;
			if (loop == 5) {
				//der er et flag
				//cout << "flag" << endl;
				stuff.push_back(0);
				loop = 0;
			}
		}
		else {
			//0
			loop = 0;
		}
	}

	//smid stuff over i bVector
	bVector.clear();

	for (bool i : stuff)
		bVector.push_back(i);
}

void DataLinkTransmit::printFrames()
{
	for (unsigned int i = 0; i < payload.size(); i++)
		cout << payload[i] << endl;
}

void DataLinkTransmit::print(vector<bool>& aVector, string aName)
{
	cout << endl << "dette er et plot af: " << aName << endl;
	int space = 0;
	for (int i : aVector)
	{
		cout << i;
		space++;
		if (space > 7)
		{
			space = 0;
			cout << " ";
		}
	}
	cout << endl;
}