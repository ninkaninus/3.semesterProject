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
	void getPayload(int index);				//finder en payload udfra indexnummer - gemmes i payload			
	void nextIndex();						
	void setStatus(bool SR);	
	void sendPayload();						//ved brug af denne funktion sendes den enkelte payload

	~TransportLayer();

protected:
	vector<int> input;						//user input
	vector<int> payload;					//pakkedel
	bool SR;								//status sender eller modtager
	int index;								//Framenummer
};

