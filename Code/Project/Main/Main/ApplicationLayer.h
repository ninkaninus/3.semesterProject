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

	//hj�lpefunktioner
	void print(vector<bool>& aVector, string aName);	// viser bits

	~ApplicationLayer();

protected:
	TransportLayer objT;
	bool sendStatus;									// Er beskeden n�et frem og klar til at sende igen
	
};