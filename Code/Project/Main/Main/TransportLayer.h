#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include "DataLinkTransmit.h"
#include "Transmitter/Transmitter/Transmitter.h"

using namespace std;


class TransportLayer
{
public:
	TransportLayer();
	void newInput(vector<bool>& anInput);
	void getPayload(int index);				//finder en payload udfra indexnummer - gemmes i payload			
	void nextIndex();						
	void setStatus(bool SR);	
	void send(vector<bool>& bVector);
	
	int returnMaxIndex();
	vector<bool> returnPayload();

	~TransportLayer();

protected:
	DataLinkTransmit objD;
	vector<bool> input;						//user input
	vector<bool> payload;					//pakkedel
	bool SR;								//status sender eller modtager
	int index;								//Framenummer
	int maxIndex;
	int CHARS_IN_FRAME;
};

