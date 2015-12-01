#include "Physical_Receive.h"



Physical_Receive::Physical_Receive()
{
}

void Physical_Receive::init(int aSampleRate, int aProcessingTime)
{
	DTMF_analyzer.init(aSampleRate, aProcessingTime);
}

void Physical_Receive::startRecording()
{
	DTMF_analyzer.startRecording();
}

void Physical_Receive::stopRecording()
{
	DTMF_analyzer.stopRecording();
}

void Physical_Receive::analyzeBuffer()
{
	//std::cout << "Size of active buffer before analysis: " << DTMF_analyzer.getActiveBuffer().size() << std::endl;

		char firstDTMF = DTMF_analyzer.syncToFirstDTMF();
		if (firstDTMF != '?')
		{
			charsReceived.push_back(firstDTMF);

			std::cout << count << ". detected char: " << firstDTMF << std::endl;
			count++;

			charStringBroken = false;
		}
		
		else
			charStringBroken = true;
}

void Physical_Receive::nextCharacter()
{
	while (DTMF_analyzer.bufferReady())
	{
		char detectedChar = DTMF_analyzer.findNextDTMF();
		if (detectedChar != '?')
		{
			charsReceived.push_back(detectedChar);
			DTMF_analyzer.erasePreviousSamples();

			std::cout << count << ". detected char: " << detectedChar << std::endl;
			count++;

		}
		else
		{
			charStringBroken = true;
			std::cout << "No more characters" << std::endl;
			break;
		}
	}
}

void Physical_Receive::continuousAnalysis()
{
	std::cout << "Buffer size: " << DTMF_analyzer.getActiveBuffer().size() << std::endl;

	DTMF_analyzer.addToBuffer();

	while (true)
	{
		if (DTMF_analyzer.bufferReady())
		{
			if (charStringBroken)
			{
				analyzeBuffer();
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
}

void Physical_Receive::printChars()
{
	for (int i = 0; i < charsReceived.size(); i++)
	{
		std::cout << i+1 << ". detected char: " << charsReceived[i] << std::endl;
	}
}

void Physical_Receive::printMagnitude(char aChar)
{
	std::vector<int> magnitudeArray;

	std::cout << "Started magnitude for whole range" << std::endl;

	for (std::size_t i = 0; i < DTMF_analyzer.getActiveBuffer().size() - DTMF_analyzer.getSampleWindow(); i += 10)
	{
		int currentMagnitude = DTMF_analyzer.getMagnitudeH(i, aChar);
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

Physical_Receive::~Physical_Receive()
{
}
