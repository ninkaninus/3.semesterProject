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
	std::cout << "Size of active buffer before analysis: " << DTMF_analyzer.getActiveBuffer().size() << std::endl;

		char firstDTMF = DTMF_analyzer.findFirstDTMF();
		if (firstDTMF != '!' && firstDTMF != '?')
		{
			charsReceived.push_back(firstDTMF);

			std::cout << "Size of active buffer after analysis: " << DTMF_analyzer.getActiveBuffer().size() << std::endl;

			for (int iterator = 2; DTMF_analyzer.getActiveBuffer().size() > DTMF_analyzer.getSampleWindow() * 2; iterator++)
			{
				char detectedChar = DTMF_analyzer.findDTMF();
				if (detectedChar != '?')
				{
					charsReceived.push_back(detectedChar);
					DTMF_analyzer.erasePreviousSamples();
				}
				else
				{
					//std::cout << "No more characters" << std::endl;
					break;
				}
			}
		}
	

		if(firstDTMF == '!')
			bufferEmpty = true;


	if (firstDTMF == '?')
		charStringBroken = true;

	std::cout << "Size of active buffer after analysis: " << DTMF_analyzer.getActiveBuffer().size() << std::endl;
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

	for (std::size_t i = 0; i < DTMF_analyzer.getSampleWindow() * 50; i += 10)
	{
		//if (getMagnitudeH(i, detectedChar) > threshold && getMagnitudeL(i, detectedChar) > threshold)
		//{
		int currentMagnitude = DTMF_analyzer.getMagnitudeL(i, aChar);
		magnitudeArray.push_back(currentMagnitude);
		//}
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


void Physical_Receive::addChar(char aChar)
{
	charsReceived.push_back(aChar);
}

Physical_Receive::~Physical_Receive()
{
}
