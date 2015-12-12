#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include "Transmitter\Transmitter\Transmitter.h"

//"Transmitter/Transmitter/Transmitter.h"

using namespace std;

class DataLinkTransmit
{
public:
	DataLinkTransmit();
	void generateCRC(vector<bool>&, int& n);
	void bitStuffing(vector<bool>& iVector);

	//void bitStuffing(vector<int>& iVector, vector<int>& stuffVector);
	void transmitFrame(DTMF::Frame frame);
	void aCKFrame(vector<bool>& aPayload, int anOption, int anAddress, int index, int maxIndex);

	~DataLinkTransmit();

	void print(vector<bool>& aVector, string aName);
	void printFrames(); //hjælpemetode til at printe under test

private:
	DTMF::Transmitter transmitter;
	int index;
	int max;
	int GENERATOR;
	int CHARS_IN_FRAME;
	int address;
	bool options;
	vector<bool> payload;
	vector<bool> stuffed;
};