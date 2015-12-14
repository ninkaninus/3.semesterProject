#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <deque>
#include "Constants.h"
#include "PhysicalReceive.h"
#include <sstream>
#include <thread>
 
using namespace std;


class DataLinkReceive
{
public:
	DataLinkReceive();
	DTMF::Frame getFrame();
	void makeMessage();

	unsigned int numberOfFrames();
	void init(int aSampleRate, int aProcessingTime);
	void startAnalysis();
	void stopAnalysis();
	
	~DataLinkReceive();

protected:

	void run();

	// funktioner 
	unsigned int getInfo(vector<bool>& bVector, int start, int stop);
	
	bool ChekCRC(vector<bool>& bVector);
	bool validFrame(vector<bool>& bVector);
	void antiBitStuffing(vector<bool>& bVector);

	//hjælpe funktioner
	void print(vector<bool>& aVector, string aName);
	string BooleanTodata(vector<bool>& bVector);		// konverterer indkommen data til bool

	// Atributter
	PhysicalReceive objR;
	vector<bool> data;
	deque<DTMF::Frame> toTrans;
	int fail;
	unsigned int sampleRate = 8000;
	unsigned int processingTime = 25;

};

