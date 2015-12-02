#include "Analyzer.h"


Analyzer::Analyzer()
{
}

void Analyzer::init(int aSampleRate, int aProcessingTime)
{
	sampleRate = aSampleRate;
	sampleWindow = aProcessingTime * sampleRate / 1000; // Processing time in ms
	myGoertzel.init(sampleWindow, sampleRate);

//---------------------------DEFAULT THRESHOLDS----------------------------------

	std::vector<int> targetFrequencies{ 697,770,852,941,1209,1336,1477,1633 };
	std::vector<float> thresholds{ 2200,2600,1500,1800,3000,2400,6100,7000 }; // De mindste peaks for hver frekvens aflæst fra grafer

	for (int i = 0; i < targetFrequencies.size(); i++)
	{
		thresholdMap[targetFrequencies[i]] = thresholds[i] * 0.7; // 70% af max virker som et udemærket threshold ud fra de foreløbige grafer
	}

}

void Analyzer::startRecording()
{
	recorder.start(sampleRate);
	isRecording = true;
}

void Analyzer::stopRecording()
{
	recorder.stop();
	addToBuffer();
	isRecording = false;
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

float Analyzer::getMagnitudeLo(int anOffset, char aChar)
{
	float magnitude;
	std::vector<signed short> tempSamples;

	for (std::size_t i = anOffset; i < sampleWindow + anOffset; i++)
	{
		tempSamples.push_back(activeBuffer[i]);
	}

	int targetFrequency = findTargetFreqLo(aChar);
	magnitude = myGoertzel.algorithm(tempSamples, sampleWindow, targetFrequency);
	return magnitude;
}

float Analyzer::getMagnitudeHi(int anOffset, char aChar)
{
	float magnitude;
	std::vector<signed short> tempSamples;

	for (std::size_t i = anOffset; i < sampleWindow + anOffset; i++)
	{
		tempSamples.push_back(activeBuffer[i]);
	}

	int targetFrequency = findTargetFreqHi(aChar);
	magnitude = myGoertzel.algorithm(tempSamples, sampleWindow, targetFrequency);
	return magnitude;
}

int Analyzer::findTargetFreqLo(char aChar)
{
	int row = 0;
	int column = 0;
	
	for (row; row < 4; row++)
	{
		if (aChar == CHAR_TABLE[row][column])
			return FREQ_LO[row];

		for (int column = 0; column < 4; column++)
		{
			if (aChar == CHAR_TABLE[row][column])
				return FREQ_LO[row];
		}
	}
	return 0;
}

int Analyzer::findTargetFreqHi(char aChar)
{
	int row = 0;
	int column = 0;

	for (row; row < 4; row++)
	{
		if (aChar == CHAR_TABLE[row][column])
			return FREQ_HI[column];

		for (int column = 0; column < 4; column++)
		{
			if (aChar == CHAR_TABLE[row][column])
				return FREQ_HI[column];
		}
	}
	return 0;
}

bool Analyzer::bufferReady()
{
	if(activeBuffer.size() < 2 * sampleWindow)
		return false;

	return true;
}

char Analyzer::syncToFirstDTMF()
{
	int offset = 0;
	char detectedChar = '?'; // Defaultkarakter der betyder at der ikke er fundet noget DTMF
	
	while (bufferReady())
	{
		detectedChar = findNextDTMF();
		if (detectedChar != '?')
		{

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



			for (std::size_t i = 0; i < sampleWindow*2; i++)
			{
					int currentMagnitude = getMagnitudeHi(i, detectedChar);
					magnitudeArray.push_back(currentMagnitude);
			}

			/*
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
			*/

			std::vector<int> tempArray = magnitudeArray;
			std::sort(tempArray.begin(), tempArray.end());
			int largestMagnitude = tempArray[tempArray.size() - 1];

			//std::cout << "Largest Magnitude: " << largestMagnitude << std::endl;

			for (std::size_t i = 0; i < magnitudeArray.size(); i++)
			{
				if (magnitudeArray[i] == largestMagnitude)
				{
					offset = i;
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
			// slet sampleWindow/4 samples fra activeBuffer og start forfra -> syncToFirstDTMF()
			activeBuffer.erase(activeBuffer.begin(), activeBuffer.begin() + int(sampleWindow/4));
		}
	}
	return detectedChar;
}

char Analyzer::findNextDTMF()
{
	int column = 5;
	int row = 5;


	for (int i = 0; i < 4; i++)
	{
		if(myGoertzel.algorithm(activeBuffer, sampleWindow, FREQ_HI[i]) > thresholdMap[FREQ_HI[i]])
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
			if (myGoertzel.algorithm(activeBuffer, sampleWindow, FREQ_LO[i]) > thresholdMap[FREQ_LO[i]])
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
		char detectedDTMF = CHAR_TABLE[row][column];
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

