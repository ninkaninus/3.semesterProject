#include "PhysicalReceive.h"
#include <exception>

PhysicalReceive::PhysicalReceive()
{
}

void PhysicalReceive::init(int aSampleRate, int aProcessingTime)
{
	DTMF_analyzer.init(aSampleRate, aProcessingTime);
	setSyncMode(true);
	isRunning = false;
	logging = false;
}

void PhysicalReceive::startRecording()
{
	std::cout << "Recording" << std::endl;
	DTMF_analyzer.startRecording();
}

void PhysicalReceive::stopRecording()
{
	std::cout << "Stopped recording" << std::endl;
	DTMF_analyzer.stopRecording();
}

void PhysicalReceive::searchBuffer()
{
	char firstDTMF = DTMF_analyzer.syncToFirstDTMF();
	if (firstDTMF != '?')
	{
		if(logging)
			charsReceived.push_back(firstDTMF);

			//std::cout << count << ". detected char: " << firstDTMF << std::endl;
			count++;

		charStringBroken = false;
	}

	else
		charStringBroken = true;
	
}

void PhysicalReceive::nextCharacter()
{
	while (DTMF_analyzer.bufferReady())
	{
		char detectedChar = DTMF_analyzer.findNextDTMF();
		if (detectedChar != '?')
		{
			if(logging)
				charsReceived.push_back(detectedChar);

			if (!preambleExpected)
				addNibble(charToNibble(detectedChar));

			checkThreshold(detectedChar);

			DTMF_analyzer.erasePreviousSamples();

			//std::cout << count << ". detected char: " << detectedChar << std::endl;
			count++;

			preambleExpected = false; // sat her for at hverken første eller anden karakter bliver pushed back i vektoren
		}
		else
		{
			charStringBroken = true;
			preambleExpected = true;
			//std::cout << "No more characters" << std::endl;
			if (logging)
			{
				charsToFile("CharsReceived.txt");
				charsReceived.clear();
			}
			break;
		}
	}
}

void PhysicalReceive::continuousAnalysis()
{
	try
	{
		if (isRunning)
			throw "Analysis is running already";

		breakAnalysis = false;
		isRunning = true;

		DTMF_analyzer.addToBuffer();

		while (!breakAnalysis)
		{
			if (DTMF_analyzer.bufferReady())
			{
				if (charStringBroken)
				{
					searchBuffer();
					//setSyncMode(true);
				}
				else
				{
					nextCharacter();
				}
			}
			else
			{
				//std::cout << " !";
				DTMF_analyzer.addToBuffer();
				Sleep(1000);
			}
		}

		//DTMF_analyzer.stopRecording();

		std::cout << "Buffer size: " << DTMF_analyzer.getActiveBuffer().size() << std::endl;
		stopRecording();
	}
	catch (std::string error)
	{
		std::cout << "Exception occured!" << std::endl;
		std::cout << error << std::endl;
	}
}


void PhysicalReceive::stopAnalysis()
{
	breakAnalysis = true;
	isRunning = false;
}

void PhysicalReceive::checkThreshold(char aChar)
{
	if (syncMode)
	{
		int loFreq = DTMF_analyzer.findTargetFreqLo(aChar);
		int hiFreq = DTMF_analyzer.findTargetFreqHi(aChar);

		if (!thresholdUpToDate[loFreq] || !thresholdUpToDate[hiFreq])
		{
			DTMF_analyzer.updateThreshold(aChar);

			thresholdUpToDate[loFreq] = true;
			thresholdUpToDate[hiFreq] = true;
		}

		std::vector<int> freqs{ 697,770,852,941,1209,1336,1477,1633 };
		bool allTrue = true;

		for (int i = 0; i < freqs.size(); i++)
		{
			if (!thresholdUpToDate[freqs[i]])
				allTrue = false;
		}

		if (allTrue)
			syncMode = false;
	}
}

void PhysicalReceive::setSyncMode(bool aBool)
{
	std::vector<int> freqs{ 697,770,852,941,1209,1336,1477,1633 };
	syncMode = aBool;

	if (syncMode)
	{
		for (int i = 0; i < freqs.size(); i++)
		{
			thresholdUpToDate[freqs[i]] = false;
		}
	}
	else
	{
		for (int i = 0; i < freqs.size(); i++)
		{
			thresholdUpToDate[freqs[i]] = true;
		}
	}
}


std::vector<bool> PhysicalReceive::getBools()
{
	return boolsReceived;
}

std::vector<bool> PhysicalReceive::charToNibble(char aChar)
{
	std::vector<bool> temp;
	switch (aChar)
	{
	case '0':
		temp = { 0,0,0,0 };
		return temp;
	case '1':
		temp = { 0,0,0,1 };
		return temp;
	case '2':
		temp = { 0,0,1,0 };
		return temp;
	case '3':
		temp = { 0,0,1,1 };
		return temp;
	case '4':
		temp = { 0,1,0,0 };
		return temp;
	case '5':
		temp = { 0,1,0,1 };
		return temp;
	case '6':
		temp = { 0,1,1,0 };
		return temp;
	case '7':
		temp = { 0,1,1,1 };
		return temp;
	case '8':
		temp = { 1,0,0,0 };
		return temp;
	case '9':
		temp = { 1,0,0,1 };
		return temp;
	case 'A':
		temp = { 1,0,1,0 };
		return temp;
	case 'B':
		temp = { 1,0,1,1 };
		return temp;
	case 'C':
		temp = { 1,1,0,0 };
		return temp;
	case 'D':
		temp = { 1,1,0,1 };
		return temp;
	case '*':
		temp = { 1,1,1,0 };
		return temp;
	case '#':
		temp = { 1,1,1,1 };
		return temp;
	default:
		std::cerr << "NIBBLE NO GOOD" << std::endl;
		break;
	}	
}

void PhysicalReceive::addNibble(std::vector<bool> aNibble)
{
	mutex.lock();
	for (int i = 0; i < 4; i++)
	{
		boolsReceived.push_back(aNibble[i]);
	}
	mutex.unlock();
}

std::vector<bool> PhysicalReceive::extractBoolVector()
{
	mutex.lock();

		std::vector<bool> temp = boolsReceived;
		boolsReceived.clear();

	mutex.unlock();

	return temp;

}

void PhysicalReceive::printChars()
{
	for (int i = 0; i < charsReceived.size(); i++)
	{
		std::cout << i+1 << ". detected char: " << charsReceived[i] << std::endl;
	}
}

void PhysicalReceive::printMagnitude(char aChar)
{
	std::vector<int> magnitudeArray;

	magnitudeArray = DTMF_analyzer.bufferMagnitudesHi(aChar);

	vectorToFile("Magnitude.txt", magnitudeArray);
}

void PhysicalReceive::printMagnitudes()
{
	//DTMF_analyzer.syncToFirstDTMF();

	std::vector<int> magnitudeArray;
	magnitudeArray = DTMF_analyzer.bufferMagnitudesLo('1'); // 697 Hz
	vectorToFile("697.txt", magnitudeArray);
	magnitudeArray.clear();

	magnitudeArray = DTMF_analyzer.bufferMagnitudesLo('4'); // 770 Hz
	vectorToFile("770.txt", magnitudeArray);
	magnitudeArray.clear();

	magnitudeArray = DTMF_analyzer.bufferMagnitudesLo('9'); // 852 Hz
	vectorToFile("852.txt", magnitudeArray);
	magnitudeArray.clear();

	magnitudeArray = DTMF_analyzer.bufferMagnitudesLo('D'); // 941 Hz
	vectorToFile("941.txt", magnitudeArray);
	magnitudeArray.clear();

	magnitudeArray = DTMF_analyzer.bufferMagnitudesHi('1'); // 1209 Hz
	vectorToFile("1209.txt", magnitudeArray);
	magnitudeArray.clear();

	magnitudeArray = DTMF_analyzer.bufferMagnitudesHi('5'); // 1336 Hz
	vectorToFile("1336.txt", magnitudeArray);
	magnitudeArray.clear();

	magnitudeArray = DTMF_analyzer.bufferMagnitudesHi('9'); // 1477 Hz
	vectorToFile("1477.txt", magnitudeArray);
	magnitudeArray.clear();

	magnitudeArray = DTMF_analyzer.bufferMagnitudesHi('D'); // 1633 Hz
	vectorToFile("1633.txt", magnitudeArray);
	magnitudeArray.clear();
}

void PhysicalReceive::vectorToFile(std::string aTitle, std::vector<int> aVector)
{
	std::ofstream outFile(aTitle);

	std::cout << "Started Writing " << aTitle << std::endl;

	for (std::size_t i = 0; i < aVector.size(); i++)
	{
		outFile << aVector[i] << '\n';
	}

	outFile.close();

	std::cout << "Stopped Writing " << aTitle << std::endl;
}

void PhysicalReceive::charsToFile(std::string aTitle)
{
	std::ofstream outFile(aTitle);

	std::cout << "Started Writing " << aTitle << std::endl;

	for (std::size_t i = 0; i < charsReceived.size(); i++)
	{
		outFile << charsReceived[i];
	}

	outFile.close();

	std::cout << "Stopped Writing " << aTitle << std::endl;
}

void PhysicalReceive::setLogging(bool b)
{
	logging = b;
}


PhysicalReceive::~PhysicalReceive()
{
}
