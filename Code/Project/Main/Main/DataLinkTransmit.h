#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include "Transmitter/Transmitter/Transmitter.h"

using namespace std;

class DataLinkTransmit
{
public:
	DataLinkTransmit();
	void generateCRC(vector<bool>&, int& n);
	void bitStuffing(vector<bool>& iVector);

	//void bitStuffing(vector<int>& iVector, vector<int>& stuffVector);
	void transmitFrame(vector<bool>& aPayload, int index, int maxIndex);

	~DataLinkTransmit();

	void print(vector<bool>& aVector, string aName);
	void printFrames(); //hjælpemetode til at printe under test

private:
	DTMF::Transmitter transmitter;
	int index;
	int max;
	int GENERATOR;
	int CHARS_IN_FRAME;
	vector<bool> payload;
	vector<bool> stuffed;

};