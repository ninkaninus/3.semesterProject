#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>

using namespace std;

class DataLinkTransmit
{
public:
	DataLinkTransmit();
	void generateCRC(vector<bool>&, int& n);
	void bitStuffing(vector<bool>& iVector);

	//void bitStuffing(vector<int>& iVector, vector<int>& stuffVector);
	void assembleFrame(vector<bool>& aPayload,int index, int maxIndex);
	~DataLinkTransmit();
	vector<bool> returnPayload();

	void print(vector<bool>& aVector, string aName);
	void printFrames(); //hj�lpemetode til at printe under test

private:
	int index;
	int max;
	int GENERATOR;
	int CHARS_IN_FRAME;
	vector<bool> payload;
	vector<bool> stuffed;

};