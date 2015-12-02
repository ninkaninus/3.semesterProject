#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <deque>
#include "PhysicalRecive.h"
#include <sstream>
 
using namespace std;

struct Frame
{
	vector<bool> payload;
	unsigned int index;
	unsigned int maxIndex;
};


class DataLinkRecive
{
public:
	DataLinkRecive();
	Frame getFrame();
	void makeFrame();
	unsigned int numberOfFrames();

	
	~DataLinkRecive();

protected:
	// funkitoner 
	unsigned int getIndex(vector<bool>& bVector);
	unsigned int getMaxIndex(vector<bool>& bVector);
	vector<bool> getPayload(vector<bool>& bVector);
	
	bool ChekCRC(vector<bool>& bVector, int& n);
	bool validFrame(vector<bool>& bVector);
	void antiBitStuffing(vector<bool>& bVector);

	//hjælpe funktioner
	void print(vector<bool>& aVector, string aName);
	string BooleanTodata(vector<bool>& bVector);		// konverterer indkommen data til bool

	// Atributter
	PhysicalRecive objR;
	vector<bool> data;
	deque<Frame> toTrans;

};

