#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include "TransportLayer.h"
#include <sstream>

using namespace std;


class ApplicationLayer
{
public:
	ApplicationLayer();				

	void send(string message);							// sender input

	vector<bool> dataToBoolean(string aString);			// konverterer indkommen data til bool

	string BooleanTodata(vector<bool>& bVector);		// konverterer indkommen data til bool

	//hjælpefunktioner
	void print(vector<bool>& aVector, string aName);	// viser bits

	~ApplicationLayer();

protected:
	TransportLayer objT;
	bool sendStatus;									// Er beskeden nået frem og klar til at sende igen
	
};

/*
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
*/