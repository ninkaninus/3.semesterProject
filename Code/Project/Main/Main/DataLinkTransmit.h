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
	void generateCRC();
	void bitStuffing(vector<int>& iVector, vector<int>& stuffVector);
	void assembleFrame(vector<int>& payload,int index);
	~DataLinkTransmit();

private:
	int index;
	int GENERATOR;
	vector<int> payload;
	vector<int> stuffed;
};

