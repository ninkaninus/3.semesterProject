#include "PhysicalReceive.h"

PhysicalReceive::PhysicalReceive()
{
}

void PhysicalReceive::init(int aSampleRate, int aProcessingTime)
{
	DTMF_analyzer.init(aSampleRate, aProcessingTime);
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
			//charsReceived.push_back(firstDTMF);

			std::cout << count << ". detected char: " << firstDTMF << std::endl;
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
			if (!preambleExpected)
			{
				charsReceived.push_back(detectedChar);
				addNibble(charToNibble(detectedChar));
			}

			DTMF_analyzer.erasePreviousSamples();

			std::cout << count << ". detected char: " << detectedChar << std::endl;
			count++;

			preambleExpected = false; // sat her for at hverken første eller anden karakter bliver pushed back i vektoren
		}
		else
		{
			charStringBroken = true;
			preambleExpected = true;
			std::cout << "No more characters" << std::endl;
			break;
		}
	}
}

void PhysicalReceive::continuousAnalysis()
{
	breakAnalysis = false;

	DTMF_analyzer.addToBuffer();

	while (!breakAnalysis)
	//while(count < 190)
	{
		if (DTMF_analyzer.bufferReady())
		{
			if (charStringBroken)
			{
				searchBuffer();
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

void PhysicalReceive::stopAnalysis()
{
	breakAnalysis = true;
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

	std::cout << "Started magnitude for whole range" << std::endl;

	for (std::size_t i = 0; i < DTMF_analyzer.getActiveBuffer().size() - DTMF_analyzer.getSampleWindow(); i += 10)
	{
		int currentMagnitude = DTMF_analyzer.getMagnitudeHi(i, aChar);
		magnitudeArray.push_back(currentMagnitude);
	}

	//---------------EXPORT MAGNITUDES-------------------
	std::ofstream outFile("Afstand.txt");

	std::cout << "Started Writing" << std::endl;

	for (std::size_t i = 0; i < magnitudeArray.size(); i++)
	{
		outFile << magnitudeArray[i] << '\n';
	}

	outFile.close();

	std::cout << "Stopped Writing" << std::endl;
	//----------------------------------------------------
}

PhysicalReceive::~PhysicalReceive()
{
}
