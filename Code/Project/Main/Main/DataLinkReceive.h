#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <deque>
#include "PhysicalReceive.h"
#include <sstream>
 
using namespace std;

struct Frame
{
	vector<bool> payload;
	unsigned int index;
	unsigned int maxIndex;
};


class DataLinkReceive
{
public:
	DataLinkReceive();
	Frame getFrame();
	void makeFrame();
	unsigned int numberOfFrames();
	void init(int aSampleRate, int aProcessingTime);
	
	~DataLinkReceive();

protected:
	// funktioner 
	unsigned int getIndex(vector<bool>& bVector);
	unsigned int getMaxIndex(vector<bool>& bVector);
	vector<bool> getPayload(vector<bool>& bVector);
	
	bool ChekCRC(vector<bool>& bVector, int& n);
	bool validFrame(vector<bool>& bVector);
	void antiBitStuffing(vector<bool>& bVector);

	//hj�lpe funktioner
	void print(vector<bool>& aVector, string aName);
	string BooleanTodata(vector<bool>& bVector);		// konverterer indkommen data til bool

	// Atributter
	PhysicalReceive objR;
	vector<bool> data;
	deque<Frame> toTrans;

};

