#include "Goertzel.h"



Goertzel::Goertzel()
{
	targetFrequencies = std::vector<int>{ 697,770,852,941,1209,1336,1477,1633 };
}

Goertzel::Goertzel(std::vector<int> tFreqArray)
{
	targetFrequencies = tFreqArray;
}

void Goertzel::init(int aSampleWindow, int aSampleRate)
{
	int     k;
	float   floatnumSamples, omega, sine, cosine;

	scalingFactor = aSampleWindow / 2.0;

	floatnumSamples = (float)aSampleWindow;

	for (int i = 0; i < targetFrequencies.size(); i++)
	{
		k = (int)(0.5 + ((floatnumSamples * targetFrequencies[i]) / aSampleRate));
		omega = (2.0 * M_PI * k) / floatnumSamples;
		sine = sin(omega);
		cosine = cos(omega);

		sineTerms[targetFrequencies[i]] = sine;
		cosineTerms[targetFrequencies[i]] = cosine;
	}

	for (int i = 0; i < aSampleWindow; i++)
	{
		hannWindow.push_back(0.5*(1 - cos(2 * M_PI*i / (aSampleWindow - 1))));
	}

	for (int i = 0; i < aSampleWindow; i++)
	{
		float temp = 0.53836 - 0.46164*cos(2 * M_PI*i / (aSampleWindow - 1));
		hammingWindow.push_back(temp);
	}

	for (int i = 0; i < aSampleWindow; i++)
	{
		float temp = 0.42659 - 0.49656 * cos(2 * M_PI*i / (aSampleWindow - 1)) + 0.076849 * cos(4 * M_PI*i / (aSampleWindow - 1));
		blackmanWindow.push_back(temp);
	}

	for (int i = 0; i < aSampleWindow; i++)
	{
		float temp = 0.3635819 - 0.4891775 * cos(2 * M_PI*i / (aSampleWindow - 1)) + 0.1365995 * cos(4 * M_PI*i / (aSampleWindow - 1)) - 0.0106411 * cos(6 * M_PI*i / (aSampleWindow - 1));
		blackmanNuttallWindow.push_back(temp);
	}

	for (int i = 0; i < aSampleWindow; i++)
	{
		float temp = 0.35875 - 0.48829 * cos(2 * M_PI*i / (aSampleWindow - 1)) + 0.14128 * cos(4 * M_PI*i / (aSampleWindow - 1)) - 0.01168 * cos(6 * M_PI*i / (aSampleWindow - 1));
		blackmanHarrisWindow.push_back(temp);
	}
}

float Goertzel::algorithm(std::vector<signed short> someSamples, int aSampleWindow, int aTargetFreq)
{
	float	coeff, q0, q1, q2, magnitude, real, imag;

	coeff = 2.0 * cosineTerms[aTargetFreq];
	q0 = 0;
	q1 = 0;
	q2 = 0;

	std::vector<signed short> temp;

	//for (int i = 0; i < aSampleWindow; i++)
	//{
	//	temp.push_back(someSamples[i]);
	//	temp[i] *= hannWindow[i];
	//}

	for (int i = 0; i<aSampleWindow; i++)
	{
		q0 = coeff * q1 - q2 + someSamples[i] * hannWindow[i];
		q2 = q1;
		q1 = q0;
	}

	real = (q1 - q2 * cosineTerms[aTargetFreq]) / scalingFactor;
	imag = (q2 * sineTerms[aTargetFreq]) / scalingFactor;

	magnitude = sqrtf(real*real + imag*imag);

	return magnitude;
}


Goertzel::~Goertzel()
{
}
