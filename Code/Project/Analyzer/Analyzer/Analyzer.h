#pragma once
#include <algorithm>
#include <fstream>
#include "Goertzel.h"
#include "MyRecorder.h"

class Analyzer
{
public:
	Analyzer();

	void init(int aSampleRate, int aProcessingTime);

	void startRecording();
	void stopRecording();

	std::vector<signed short> getActiveBuffer();
	int getSampleWindow();
	void addToBuffer();

	float getMagnitudeL(int anOffset, char aChar);
	float getMagnitudeH(int anOffset, char aChar);
	int findTargetFreqL(char aChar);	
	int findTargetFreqH(char aChar);
	char findFirstDTMF();
	char findDTMF();
	void erasePreviousSamples();
	~Analyzer();
protected:
	const int freqH[4]{ 1209,1336,1477,1633 };
	const int freqL[4]{ 697,770,852,941 };
	const char charTable[4][4]{ { '1','2','3','A' },{ '4','5','6','B' },{ '7','8','9','C' },{ '*','0','#','D' } };
	
	const float threshold = 2000;
	bool isRecording;
	
	std::size_t sampleWindow;
	int sampleRate;

	std::vector<signed short> activeBuffer;

	MyRecorder recorder;
	Goertzel myGoertzel;
};

