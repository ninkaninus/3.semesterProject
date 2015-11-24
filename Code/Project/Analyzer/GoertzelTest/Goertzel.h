#pragma once
#include <vector>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
class Goertzel
{
public:
	Goertzel();
	Goertzel(std::vector<int> tFreqArray);
	void init(int aSampleWindow, int aSampleRate);
	float algorithm(std::vector<signed short> someSamples, int aSampleWindow, int aTargetFreq);
	~Goertzel();
protected:
	std::map<int,float> sineTerms;
	std::map<int,float> cosineTerms;

	std::vector<int> targetFrequencies;
	float scalingFactor;
};

