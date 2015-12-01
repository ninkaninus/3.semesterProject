#pragma once
#include "Analyzer.h"

class Physical_Receive
{
public:
	Physical_Receive();

	void init(int aSampleRate, int aProcessingTime);
	void startRecording();
	void stopRecording();

	void searchBuffer();
	void nextCharacter();
	void continuousAnalysis();

	void stopAnalysis();

	std::vector<bool> charToNibble(char aChar);
	void addNibble(std::vector<bool> aNibble);

	std::vector<bool> extractBoolVector();

	void printChars();
	void printMagnitude(char aChar);

	~Physical_Receive();
protected:
	Analyzer DTMF_analyzer;
	sf::Mutex mutex;
	std::vector<char> charsReceived;
	std::vector<bool> boolsReceived;

	bool breakAnalysis;
	bool charStringBroken;
	bool preambleExpected;

	int count = 1;
};

