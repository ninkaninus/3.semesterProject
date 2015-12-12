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

	std::vector<float> thresholds{ 1000,1000,1000,1000,1000,1000,1000,1000 }; 
	float ratio = 0.6;

	for (int i = 0; i < 4; i++)
	{
		thresholdMap[FREQ_LO[i]] = thresholds[i] * ratio; 
		thresholdMap[FREQ_HI[i]] = thresholds[i + 4] * ratio;
	}
}

void Analyzer::startRecording()
{
	recorder.start(sampleRate);
	//isRecording = true;
}

void Analyzer::stopRecording()
{
	recorder.stop();
	addToBuffer();
	//isRecording = false;
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

std::vector<int> Analyzer::bufferMagnitudesLo(char aChar)
{
	std::vector<int> magnitudeArray;

	//std::cout << "Started magnitude for whole range" << std::endl;

	for (std::size_t i = 0; i < activeBuffer.size() - sampleWindow; i += 10)
	{
		int currentMagnitude = getMagnitudeLo(i, aChar);
		magnitudeArray.push_back(currentMagnitude);
	}
	return magnitudeArray;
}

std::vector<int> Analyzer::bufferMagnitudesHi(char aChar)
{
	std::vector<int> magnitudeArray;

	//std::cout << "Started magnitude for whole range" << std::endl;

	for (std::size_t i = 0; i < activeBuffer.size() - sampleWindow; i += 10)
	{
		int currentMagnitude = getMagnitudeHi(i, aChar);
		magnitudeArray.push_back(currentMagnitude);
	}
	return magnitudeArray;
}

bool Analyzer::bufferReady()
{
	if(activeBuffer.size() < 4 * sampleWindow)
		return false;

	return true;
}

void Analyzer::updateThreshold(char aChar)
{
	int loFreq = findTargetFreqLo(aChar);
	int hiFreq = findTargetFreqHi(aChar);
	float loMag = getMagnitudeLo(0, aChar);
	float hiMag = getMagnitudeHi(0, aChar);
	thresholdMap[loFreq] = loMag * 0.75;
	thresholdMap[hiFreq] = hiMag * 0.75;
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
			std::vector<int> magnitudeArray;

			for (std::size_t i = 0; i < sampleWindow*2; i++)
			{
					int currentMagnitude = getMagnitudeHi(i, detectedChar);
					magnitudeArray.push_back(currentMagnitude);
			}

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

