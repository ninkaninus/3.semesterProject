#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>

using namespace std;


class TransportLayer
{
public:
	TransportLayer();
	void newInput(vector<bool>& anInput);
	void getPayload(int index);				//finder en payload udfra indexnummer - gemmes i payload			
	void nextIndex();						
	void setStatus(bool SR);	
	void sendPayload();						//ved brug af denne funktion sendes den enkelte payload
	vector<bool> returnPayload();

	~TransportLayer();

protected:
	vector<bool> input;						//user input
	vector<bool> payload;					//pakkedel
	bool SR;								//status sender eller modtager
	int index;								//Framenummer
	int maxIndex;
	int CHARS_IN_FRAME;
};

