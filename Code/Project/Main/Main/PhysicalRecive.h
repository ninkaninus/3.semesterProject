#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>

using namespace std;

class PhysicalRecive
{
public:
	PhysicalRecive();
	bool getStatus();				//
	void randomWait(int k);			//fejler den i at sende skal den vente med at sende igen

	~PhysicalRecive();

protected:
	bool status;					//status er den klar til at sende næste frame
	vector<int> frame;
	int k;							//hvormange gange har den mislykkeds i at afsende framen?
};

