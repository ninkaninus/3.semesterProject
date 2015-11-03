#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>

using namespace std;

class PhysicalTransmit
{
public:
	PhysicalTransmit();
	bool getStatus();
	bool frameEndDetect();
	~PhysicalTransmit();

protected:
	vector<int> recivedFrame;
	// eventuelt en opbevaring af sampling 
	int index;
};

