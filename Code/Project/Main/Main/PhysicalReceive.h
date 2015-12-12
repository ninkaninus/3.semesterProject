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

	void checkThreshold(char aChar);
	void setSyncMode(bool aBool);

	std::vector<bool> getBools();

	std::vector<bool> charToNibble(char aChar);
	void addNibble(std::vector<bool> aNibble);

	std::vector<bool> extractBoolVector();

	void printChars();
	void printMagnitude(char aChar);
	void printMagnitudes();
	void vectorToFile(std::string aTitle, std::vector<int> aVector);
	void charsToFile(std::string aTitle);
	void setLogging(bool b);

	~PhysicalReceive();
protected:
	Analyzer DTMF_analyzer;
	sf::Mutex mutex;
	std::vector<char> charsReceived;
	std::vector<bool> boolsReceived;

	bool isRunning;
	bool breakAnalysis;
	bool charStringBroken;
	bool preambleExpected;
	bool logging;

	std::map<int, bool> thresholdUpToDate;
	bool syncMode;

	int count = 1;
};

