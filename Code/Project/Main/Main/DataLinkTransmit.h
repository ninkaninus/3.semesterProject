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
	void generateCRC(vector<int>&);
	//void bitStuffing(vector<int>& iVector, vector<int>& stuffVector);
	void assembleFrame(vector<bool>& aPayload,int index, int maxIndex);
	~DataLinkTransmit();

	void printFrames(); //hjælpemetode til at printe under test

private:
	int index;
	int max;
	int GENERATOR;
	int CHARS_IN_FRAME;
	vector<bool> payload;
	vector<bool> stuffed;

};