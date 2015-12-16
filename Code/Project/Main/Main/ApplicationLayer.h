#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <random>
#include <bitset>
#include "TransportLayer.h"

using namespace std;


class ApplicationLayer
{
public:
	ApplicationLayer();				

	void send(string message);							// sender input

	vector<bool> dataToBoolean(string aString);			// konverterer indkommen data til bool
	string booleanTodata(vector<bool>& bVector);		// konverterer indkommen data til bool

	void newMessage();
	void handleTransmit();
	void handleReceive();

	void loop();

	//hjælpefunktioner
	void print(vector<bool>& aVector, string aName);	// viser bits

	~ApplicationLayer();

protected:
	TransportLayer objT;
	bool sendStatus;									// Er beskeden nået frem og klar til at sende igen
	bool messageComplete = true;
	int lengthOfMessage;
	std::string messageIn;
	deque<std::string> messageInBuffer;
	deque<std::string> messageOutBuffer;
	deque<std::vector<bool>*> currentBuffer;
	const unsigned int BITS_IN_FRAME = 160 * 8;
	sf::Mutex mutex;
};

