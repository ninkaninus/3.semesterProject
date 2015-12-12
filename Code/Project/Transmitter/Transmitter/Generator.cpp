#include "Generator.h"
#include <iostream>
#include <stdlib.h>
#include <Constants.h>

namespace DTMF {

	Generator::Generator()
	{
	}

	void Generator::setSampleRate(unsigned int aNumber) 
	{
		sampleRate = aNumber;
	}

	unsigned int Generator::getSampleRate() const 
	{
		return sampleRate;
	}

	unsigned int Generator::getVolumeMax() const 
	{
		return volumeMax;
	}

	void Generator::setVolumeMax(unsigned int aNumber) 
	{
		volumeMax = aNumber;
	}

	double Generator::getDuration() const 
	{
		return duration;
	}

	void Generator::setDuration(double aNumber) 
	{
		duration = aNumber;
	}

	void Generator::setVolumeSmoothing(bool b) {
		volumeSmoothing = b;
	}

	bool Generator::getVolumeSmoothing() const {
		return volumeSmoothing;
	}

	/*
	sf::SoundBuffer* Generator::generate(std::vector<bool> binarySequence)
	{
		std::vector<DTMF::Tone> tones;

		return generate(tones);
	}
	*/

	sf::SoundBuffer* Generator::generate(std::vector<DTMF::Tone>& toneBuffer) 
	{
		unsigned int bufferSize = static_cast<unsigned int>((toneBuffer.size() * sampleRate) * duration);

		sf::SoundBuffer* SBpoint = new sf::SoundBuffer();

		sf::Int16* outputBuffer = nullptr;

		switch (trans)
		{
		case DTMF::snap:
			outputBuffer = transitionSnap(toneBuffer, bufferSize);
			break;
		case DTMF::triangle:
			outputBuffer = transitionTriangle(toneBuffer, bufferSize);
			break;
		case DTMF::steep:
			outputBuffer = transitionSteep(toneBuffer, bufferSize, STEEP_PERCENT);
			break;
		case DTMF::smooth:
			outputBuffer = transitionSmooth(toneBuffer, bufferSize);
			break;
		default:
			break;
		}

		SBpoint->loadFromSamples(&outputBuffer[0], bufferSize, 1, sampleRate);
		//SBpoint->saveToFile("Test_Generator_Steep_10.ogg");

		return SBpoint;
	}

	sf::Int16* Generator::transitionSmooth(std::vector<DTMF::Tone>& toneBuffer, unsigned int bufferSize) {

		sf::Int16* outputBuffer = new sf::Int16[bufferSize];

		int samplesPerTone = bufferSize / toneBuffer.size();

		//Declarations
		double phase1 = 0;
		double phase2 = 0;
		double phaseAdj1 = 0;
		double phaseAdj2 = 0;

		for (int i = 0; i < toneBuffer.size(); i++)
		{
			ToneFreq freq = getFreq(toneBuffer[i]);
			phaseAdj1 = (freq.frequency1 * (DTMF::TWO_PI) / (sampleRate));
			phaseAdj2 = (freq.frequency2 * (DTMF::TWO_PI) / (sampleRate));

			if (i == 0) {
				phase1 = 0;
				phase2 = 0;
			}
			else {
				bool foundPhase = false;
				int numb = 0;
				if (outputBuffer[(i * samplesPerTone) - 1] < 0) {
					while (!foundPhase) {
						numb = volumeMax * (std::sin(phase1) + std::sin(phase2));
						if (numb > outputBuffer[(i * samplesPerTone) - 1]) {
							phase1 -= phaseAdj1;
							phase2 -= phaseAdj2;
						}
						else {
							foundPhase = true;
						}
					}
				} else {
					while (!foundPhase) {
						numb = volumeMax * (std::sin(phase1) + std::sin(phase2));
						if (numb < outputBuffer[(i * samplesPerTone) - 1]) {
							phase1 += phaseAdj1;
							phase2 += phaseAdj2;
						}
						else {
							foundPhase = true;
						}
					}
				}
			}
			
			for (int j = i * samplesPerTone; j < (i + 1) * samplesPerTone; j++)
			{

				outputBuffer[j] = static_cast<sf::Int16>(volumeMax * (std::sin(phase1) + std::sin(phase2)));

				phase1 += phaseAdj1;
				phase2 += phaseAdj2;

				if (phase1 >= TWO_PI) phase1 -= TWO_PI;
				if (phase2 >= TWO_PI) phase2 -= TWO_PI;
			}
		}

		return outputBuffer;
	}

	sf::Int16* Generator::transitionSteep(std::vector<DTMF::Tone>& toneBuffer, unsigned int bufferSize, double percentToMax) {
		sf::Int16* outputBuffer = new sf::Int16[bufferSize];

		int samplesPerTone = bufferSize / toneBuffer.size();

		//Declarations
		double phase1 = 0;
		double phase2 = 0;
		double phaseAdj1 = 0;
		double phaseAdj2 = 0;
		double volume = 0;
		int transitionToneAmount = int((samplesPerTone / 100.0) * percentToMax);
		double volumeAdj = double(volumeMax) / transitionToneAmount;
		bool volumeRising = true;

		for (int i = 0; i < toneBuffer.size(); i++)
		{
			//The values to be set every tone
			phase1 = 0;
			phase2 = 0;
			volume = 0.0;
			volumeRising = true;
			ToneFreq freq = getFreq(toneBuffer[i]);
			phaseAdj1 = (freq.frequency1 * (DTMF::TWO_PI) / (sampleRate));
			phaseAdj2 = (freq.frequency2 * (DTMF::TWO_PI) / (sampleRate));
			unsigned int endTransition = ((i + 1) * samplesPerTone) - transitionToneAmount;

			for (int j = i * samplesPerTone; j < (i + 1) * samplesPerTone; j++)
			{

				outputBuffer[j] = static_cast<sf::Int16>(volume * (std::sin(phase1) + std::sin(phase2)));

				phase1 += phaseAdj1;
				phase2 += phaseAdj2;

				if (phase1 >= TWO_PI) phase1 -= TWO_PI;
				if (phase2 >= TWO_PI) phase2 -= TWO_PI;

				if (volumeRising) {
					volume += volumeAdj;
				}
				else if(!volumeRising && j <  endTransition){
					volume = volumeMax;
				}

				else {
					volume -= volumeAdj;
				}

				if (volume > volumeMax) {
					volume -= volumeAdj;
					volumeRising = false;
				}

			}
		}

		return outputBuffer;
	}

	sf::Int16* Generator::transitionTriangle(std::vector<DTMF::Tone>& toneBuffer, unsigned int bufferSize) {
		return transitionSteep(toneBuffer, bufferSize, 50);
	}

	sf::Int16* Generator::transitionSnap(std::vector<DTMF::Tone>& toneBuffer, unsigned int bufferSize) {

		sf::Int16* outputBuffer = new sf::Int16[bufferSize];

		int samplesPerTone = bufferSize / toneBuffer.size();

		//Declarations
		double phase1 = 0;
		double phase2 = 0;
		double phaseAdj1 = 0;
		double phaseAdj2 = 0;

		for (int i = 0; i < toneBuffer.size(); i++)
		{
			//The values to be set every tone
			phase1 = 0;
			phase2 = 0;
			ToneFreq freq = getFreq(toneBuffer[i]);
			phaseAdj1 = (freq.frequency1 * (DTMF::TWO_PI) / (sampleRate));
			phaseAdj2 = (freq.frequency2 * (DTMF::TWO_PI) / (sampleRate));

			for (int j = i * samplesPerTone; j < (i + 1) * samplesPerTone; j++)
			{

				outputBuffer[j] = static_cast<sf::Int16>(volumeMax * (std::sin(phase1) + std::sin(phase2)));

				phase1 += phaseAdj1;
				phase2 += phaseAdj2;

				if (phase1 >= TWO_PI) phase1 -= TWO_PI;
				if (phase2 >= TWO_PI) phase2 -= TWO_PI;
			}
		}

		return outputBuffer;
	}

	DTMF::ToneFreq Generator::getFreq(DTMF::Tone tone) 
	{

		ToneFreq freq;

		switch (tone)
		{
		case DTMF::ZERO:
			freq.frequency1 = 941;
			freq.frequency2 = 1336;
			return freq;
		case DTMF::ONE:
			freq.frequency1 = 697;
			freq.frequency2 = 1209;
			return freq;
		case DTMF::TWO:
			freq.frequency1 = 697;
			freq.frequency2 = 1336;
			return freq;
		case DTMF::THREE:
			freq.frequency1 = 697;
			freq.frequency2 = 1477;
			return freq;
		case DTMF::FOUR:
			freq.frequency1 = 770;
			freq.frequency2 = 1209;
			return freq;
		case DTMF::FIVE:
			freq.frequency1 = 770;
			freq.frequency2 = 1336;
			return freq;
		case DTMF::SIX:
			freq.frequency1 = 770;
			freq.frequency2 = 1477;
			return freq;
		case DTMF::SEVEN:
			freq.frequency1 = 852;
			freq.frequency2 = 1209;
			return freq;
		case DTMF::EIGHT:
			freq.frequency1 = 852;
			freq.frequency2 = 1336;
			return freq;
		case DTMF::NINE:
			freq.frequency1 = 852;
			freq.frequency2 = 1477;
			return freq;
		case DTMF::A:
			freq.frequency1 = 697;
			freq.frequency2 = 1633;
			return freq;
		case DTMF::B:
			freq.frequency1 = 770;
			freq.frequency2 = 1633;
			return freq;
		case DTMF::C:
			freq.frequency1 = 852;
			freq.frequency2 = 1633;
			return freq;
		case DTMF::D:
			freq.frequency1 = 941;
			freq.frequency2 = 1633;
			return freq;
		case DTMF::ASTERISK:
			freq.frequency1 = 941;
			freq.frequency2 = 1209;
			return freq;
		case DTMF::HASH:
			freq.frequency1 = 941;
			freq.frequency2 = 1477;
			return freq;
		default:
			break;
		}
	}

	Generator::~Generator()
	{
	}

}