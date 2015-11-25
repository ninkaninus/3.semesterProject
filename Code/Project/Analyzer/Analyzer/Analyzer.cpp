#include "Analyzer.h"


Analyzer::Analyzer()
{
}

void Analyzer::init(int aSampleRate, int aProcessingTime)
{
	sampleRate = aSampleRate;
	sampleWindow = aProcessingTime * sampleRate / 1000; // Processing time in ms
	myGoertzel.init(sampleWindow, sampleRate);
}

void Analyzer::startRecording()
{
	recorder.start(sampleRate);
}

void Analyzer::stopRecording()
{
	recorder.stop();
	addToBuffer();
}

std::vector<signed short> Analyzer::getActiveBuffer()
{
	return activeBuffer;
}

int Analyzer::getSampleWindow()
{
	return sampleWindow;
}

void Analyzer::addToBuffer()
{
	std::vector<signed short> aBuffer = recorder.extractBuffer();

	for (std::size_t i = 0; i < aBuffer.size(); i++)
	{
		activeBuffer.push_back(aBuffer[i]);
	}
}

float Analyzer::getMagnitudeL(int anOffset, char aChar)
{
	float magnitude;
	std::vector<signed short> tempSamples;

	for (std::size_t i = anOffset; i < sampleWindow + anOffset; i++)
	{
		tempSamples.push_back(activeBuffer[i]);
	}

	int targetFrequency = findTargetFreqL(aChar);
	magnitude = myGoertzel.algorithm(tempSamples, sampleWindow, targetFrequency);
	return magnitude;
}

float Analyzer::getMagnitudeH(int anOffset, char aChar)
{
	float magnitude;
	std::vector<signed short> tempSamples;

	for (std::size_t i = anOffset; i < sampleWindow + anOffset; i++)
	{
		tempSamples.push_back(activeBuffer[i]);
	}

	int targetFrequency = findTargetFreqH(aChar);
	magnitude = myGoertzel.algorithm(tempSamples, sampleWindow, targetFrequency);
	return magnitude;
}

int Analyzer::findTargetFreqL(char aChar)
{
	int row = 0;
	int column = 0;
	
	for (row; row < 4; row++)
	{
		if (aChar == charTable[row][column])
			return freqL[row];

		for (int column = 0; column < 4; column++)
		{
			if (aChar == charTable[row][column])
				return freqL[row];
		}
	}
	return 0;
}

int Analyzer::findTargetFreqH(char aChar)
{
	int row = 0;
	int column = 0;

	for (row; row < 4; row++)
	{
		if (aChar == charTable[row][column])
			return freqH[column];

		for (int column = 0; column < 4; column++)
		{
			if (aChar == charTable[row][column])
				return freqH[column];
		}
	}
	return 0;
}

char Analyzer::findFirstDTMF()
{
	int offset = 0;
	char detectedChar = '!';
	
	while (activeBuffer.size() > 2 * sampleWindow)
	{
		detectedChar = findDTMF();
		if (detectedChar != '?')
		{
			isRecording = true;

			/*
			//-----------------EXPORT MAGNITUDES FOR FIRST CHAR-----------------
			std::ofstream outFile2("Fon.txt");

			std::cout << "Started Writing" << std::endl;

			for (int i = 0; i < 2000; i++)
			{
				outFile2 << myGoertzel.algorithm(activeBuffer, sampleWindow, i) << '\n';

			}

			outFile2.close();
			std::cout << "Stopped Writing" << std::endl;
			//-------------------------------------------------------------------
			*/

			std::vector<int> magnitudeArray;

			for (std::size_t i = 0; i < sampleWindow*2; i += 10)
			{
				//if (getMagnitudeH(i, detectedChar) > threshold && getMagnitudeL(i, detectedChar) > threshold)
				//{
					int currentMagnitude = getMagnitudeH(i, detectedChar);
					magnitudeArray.push_back(currentMagnitude);
				//}
			}

			
			//---------------EXPORT MAGNITUDES-------------------
			std::ofstream outFile("TestH.txt");

			std::cout << "Started Writing" << std::endl;

			for (std::size_t i = 0; i < magnitudeArray.size(); i++)
			{
				outFile << magnitudeArray[i] << '\n';
			}

			outFile.close();

			std::cout << "Stopped Writing" << std::endl;
			//----------------------------------------------------
			

			std::vector<int> tempArray = magnitudeArray;
			std::sort(tempArray.begin(), tempArray.end());
			int largestMagnitude = tempArray[tempArray.size() - 1];

			std::cout << "Largest Magnitude: " << largestMagnitude << std::endl;

			for (std::size_t i = 0; i < magnitudeArray.size(); i++)
			{
				if (magnitudeArray[i] == largestMagnitude)
				{
					offset = i*10;
					break;
				}
			}


			activeBuffer.erase(activeBuffer.begin(), activeBuffer.begin() + offset + sampleWindow);
			return detectedChar;
			// lav et array med magnitudes til den fundne karakter og sæt offset til der hvor magnitude er højest.
			// Slet alle samples før offset + sampleWindow.
		}
		else
		{
			// slet sampleWindow/10 samples fra activeBuffer og start forfra -> findFirstDTMF()
			activeBuffer.erase(activeBuffer.begin(), activeBuffer.begin() + sampleWindow/10);
		}
	}
	return detectedChar;
}

char Analyzer::findDTMF()
{
	int column = 5;
	int row = 5;


	for (int i = 0; i < 4; i++)
	{
		if(myGoertzel.algorithm(activeBuffer, sampleWindow, freqH[i]) > threshold)
		{
			column = i;
			break;
		}
	}
	if (column == 5)
	{
		//std::cout << "Ain't no thang here 1" << std::endl;
		return '?';
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (myGoertzel.algorithm(activeBuffer, sampleWindow, freqL[i]) > threshold)
			{
				row = i;
				break;
			}
		}
	}

	if (row == 5)
	{
		//std::cout << "Ain't no thang here 2" << std::endl;
		return '?';
	}
	else
	{
		char detectedDTMF = charTable[row][column];
		return detectedDTMF;
	}
}
void Analyzer::erasePreviousSamples()
{
	activeBuffer.erase(activeBuffer.begin(), activeBuffer.begin() + sampleWindow);
}

Analyzer::~Analyzer()
{
}

