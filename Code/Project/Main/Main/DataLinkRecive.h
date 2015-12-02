#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <deque>
#include "PhysicalRecive.h"
 
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
	void makeFrame();
	Frame getFrame();
	
	unsigned int numberOfFrames();
	
	void print(vector<bool>& aVector, string aName);
	
	//vector<bool> getIndex();
	//vector<bool> getMaxIndex();
	//vector<bool> extractPayload();
	//bool checkCRC();
	//bool validFrame();
	//void antiBitStuffing();	
	
	~DataLinkRecive();

protected:
	PhysicalRecive objR;
	vector<bool> data;
	deque<Frame> toTrans;

};

