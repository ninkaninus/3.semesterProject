#pragma once
#include "Analyzer.h"
#include <thread>

class PhysicalReceive
{
public:
	PhysicalReceive();

	void init(int aSampleRate, int aProcessingTime);
	void startRecording();
	void stopRecording();

	void searchBuffer();
	void nextCharacter();

	void continuousAnalysis();
	void stopAnalysis();

	bool syncNeeded(char aChar);
	void setSyncMode();
	void syncThresholds();

	std::vector<bool> getBools();

	std::vector<bool> charToNibble(char aChar);
	void addNibble(std::vector<bool> aNibble);

	std::vector<bool> extractBoolVector();

	void printChars();
	void printMagnitude(char aChar);
	void printMagnitudes();
	void vectorToFile(std::string aTitle, std::vector<int> aVector);

	~PhysicalReceive();
protected:
	Analyzer DTMF_analyzer;
	sf::Mutex mutex;
	std::vector<char> charsReceived;
	std::vector<bool> boolsReceived;

	std::map<char, bool> charSynced;
	bool isRecording;
	bool breakAnalysis;
	bool charStringBroken;
	bool preambleExpected;
	bool syncMode;

	int count = 1;
};

