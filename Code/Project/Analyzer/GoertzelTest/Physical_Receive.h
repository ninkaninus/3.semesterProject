#pragma once
#include "Analyzer.h"
class Physical_Receive
{
public:
	Physical_Receive();
	~Physical_Receive();

protected:
	Analyzer DTMF_analyzer;
	std::vector<char> charsReceived;
};

