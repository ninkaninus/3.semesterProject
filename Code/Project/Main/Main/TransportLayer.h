#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <chrono>
#include <thread>
#include "DataLinkTransmit.h"
#include "DataLinkReceive.h"
#include <SFML\System\Mutex.hpp>

using namespace std;

class TransportLayer
{
public:
	TransportLayer();
	void calculateIndex(unsigned int payloadSize);
	vector<bool> extractPayload(unsigned int index);
	void setStatus(bool SR);
	void send(vector<bool>& bVector);

	int returnMaxIndex() const;

	~TransportLayer();

protected:
	DataLinkTransmit dataLinkT;
	vector<bool> input;						//user input
	bool SR;								//status sender eller modtager
	int index;								//Framenummer
	int maxIndex;
	const unsigned int BITS_IN_FRAME = 160 * 8;
};
