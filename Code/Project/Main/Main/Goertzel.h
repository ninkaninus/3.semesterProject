#pragma once
#include <vector>
#include <deque>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
class Goertzel
{
public:
	Goertzel();
	Goertzel(std::vector<int> tFreqArray);
	void init(int aSampleWindow, int aSampleRate);
	float algorithm(std::deque<signed short> someSamples, int aSampleWindow, int aTargetFreq);
	~Goertzel();
protected:
	std::map<int,float> sineTerms;
	std::map<int,float> cosineTerms;

	std::vector<float> hannWindow;
	std::vector<float> hammingWindow;
	std::vector<float> blackmanWindow;
	std::vector<float> blackmanNuttallWindow;
	std::vector<float> blackmanHarrisWindow;

	std::vector<int> targetFrequencies;
	float scalingFactor;
};

