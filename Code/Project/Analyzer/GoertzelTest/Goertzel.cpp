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
}

float Goertzel::algorithm(std::vector<signed short> someSamples, int aSampleWindow, int aTargetFreq)
{
	float	coeff, q0, q1, q2, magnitude, real, imag;

	coeff = 2.0 * cosineTerms[aTargetFreq];
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (int i = 0; i<aSampleWindow; i++)
	{
		q0 = coeff * q1 - q2 + someSamples[i];
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
