#pragma once
#include "Analyzer.h"
class Physical_Receive
{
public:
	Physical_Receive();

	void init(int aSampleRate, int aProcessingTime);
	void startRecording();
	void stopRecording();

	void analyzeBuffer();
	void nextCharacter();
	void continuousAnalysis();

	void printChars();
	void printMagnitude(char aChar);

	void addChar(char aChar);
	~Physical_Receive();

protected:
	Analyzer DTMF_analyzer;
	std::vector<char> charsReceived;

	bool charStringBroken;

	int count = 1;
};

