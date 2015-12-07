#pragma once
#include <algorithm>
#include <fstream>
#include <Windows.h>
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

	float getMagnitudeLo(int anOffset, char aChar);
	float getMagnitudeHi(int anOffset, char aChar);
	int findTargetFreqLo(char aChar);	
	int findTargetFreqHi(char aChar);
	std::vector<int> bufferMagnitudesLo(char aChar);
	std::vector<int> bufferMagnitudesHi(char aChar);

	bool bufferReady();
	void updateThresholds(int aFrequency, float aMagnitude);

	char syncToFirstDTMF();
	char findNextDTMF();
	void erasePreviousSamples();
	~Analyzer();
protected:
	const int FREQ_HI[4]{ 1209,1336,1477,1633 };
	const int FREQ_LO[4]{ 697,770,852,941 };
	const char CHAR_TABLE[4][4]{ { '1','2','3','A' },{ '4','5','6','B' },{ '7','8','9','C' },{ '*','0','#','D' } };
	
	std::map<int, float> thresholdMap;
	
	std::size_t sampleWindow;
	int sampleRate;

	std::vector<signed short> activeBuffer;

	MyRecorder recorder;
	Goertzel myGoertzel;
};

