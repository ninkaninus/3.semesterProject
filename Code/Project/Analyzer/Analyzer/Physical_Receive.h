#pragma once
#include "Analyzer.h"
#include <thread>

class Physical_Receive
{
public:
	Physical_Receive();

	void init(int aSampleRate, int aProcessingTime);
	void startRecording();
	void stopRecording();

	void continuousAnalysis();
	void stopAnalysis();

	std::vector<bool> getBools();
	std::vector<bool> extractBoolVector();

	void printChars();
	void printMagnitude(char aChar);

	~Physical_Receive();
protected:
	void searchBuffer();
	void nextCharacter();

	std::vector<bool> charToNibble(char aChar);
	void addNibble(std::vector<bool> aNibble);

	Analyzer DTMF_analyzer;
	sf::Mutex mutex;

	std::vector<char> charsReceived;
	std::vector<bool> boolsReceived;

	bool breakAnalysis;
	bool charStringBroken;
	bool preambleExpected;

	int count = 1;
};

