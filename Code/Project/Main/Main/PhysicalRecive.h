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

	~PhysicalRecive();

	// til test - Datalink recieve
	vector<bool> extractBoolVector();					//
	void setCharInBool(vector<bool>& bVector);		//

protected:
	bool status;					//status er den klar til at sende næste frame
	vector<int> frame; 
	int k;							//hvormange gange har den mislykkeds i at afsende framen?
	
	// til test - Datalink recieve
	vector<bool> CharBool;
};

