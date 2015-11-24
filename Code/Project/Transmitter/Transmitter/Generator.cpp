#include "Generator.h"
#include <iostream>
#include <stdlib.h>

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

	void Generator::setTransitionMode(Transition mode) 
	{
		transition = mode;
	}

	Transition Generator::getTransitionMode() const 
	{
		return transition;
	}

	sf::SoundBuffer* Generator::generate(std::vector<bool> binarySequence)
	{
		std::vector<DTMF::Tone> tones;

		return generate(tones);
	}

	sf::SoundBuffer* Generator::generate(std::vector<DTMF::Tone> toneBuffer) 
	{
		unsigned int bufferSize = static_cast<unsigned int>((toneBuffer.size() * sampleRate) * duration);
		sf::SoundBuffer* SBpoint = new sf::SoundBuffer();
		sf::Int16* outputBuffer = new sf::Int16[bufferSize];

		int samplesPerTone = bufferSize / toneBuffer.size();

		double phase1 = 0;
		double phase2 = 0;
		double phaseAdj1 = 0;
		double phaseAdj2 = 0;
		double volume = 0.0;
		double volumeAdj = double(volumeMax) / (samplesPerTone/2);
		bool volumeRising = true;

		for (int i = 0; i < toneBuffer.size(); i++) 
		{
			phase1 = 0;
			phase2 = 0;
			volume = 0.0;
			volumeRising = true;

			ToneFreq freq = getFreq(toneBuffer[i]);

			phaseAdj1 = (freq.frequency1 * (DTMF::TWO_PI) / (sampleRate));
			phaseAdj2 = (freq.frequency2 * (DTMF::TWO_PI) / (sampleRate));

			for (int j = i * samplesPerTone; j < (i + 1) * samplesPerTone; j++) 
			{

				outputBuffer[j] = static_cast<sf::Int16>(volume * (std::sin(phase1) + std::sin(phase2)));

				phase1 += phaseAdj1;
				phase2 += phaseAdj2;

				if (phase1 >= TWO_PI) phase1 -= TWO_PI;
				if (phase2 >= TWO_PI) phase2 -= TWO_PI;
				if (volume >= volumeMax) {
					volumeRising = false;
				}

				if (volumeRising) {
					volume += volumeAdj;
				}
				else {
					volume -= volumeAdj;
				}
			}
		}

		if (transition == Transition::zeroPadding)
		{
			int currentIndex = 0;

			bool peaked = false;

			for (int i = 1; i < toneBuffer.size() - 1; i++) 
			{
				currentIndex = (i * samplesPerTone);
				peaked = false;

				do 
				{
					std::cout << "Current Index Value: " << outputBuffer[currentIndex] << std::endl;
					std::cout << "Next Index Value: " << outputBuffer[currentIndex - 1] << std::endl;
					if (std::abs(outputBuffer[currentIndex - 1]) < std::abs(outputBuffer[currentIndex]))
					{
						peaked = true;
						outputBuffer[currentIndex] = 0;
						std::cout << "Peaked" <<std::endl;
					}
					else
					{
						outputBuffer[currentIndex] = 0;
						std::cout << "Haven't Peaked Yet" << std::endl;
					}

					currentIndex--;

				} while (peaked == false);

				std::cout << "Done with the peaking" << std::endl << std::endl;

				while(std::abs(outputBuffer[currentIndex - 1]) < std::abs(outputBuffer[currentIndex]))
				{
					std::cout << "Next Index Value: " << outputBuffer[currentIndex - 1] << std::endl;
					std::cout << "Current Index Value: " << outputBuffer[currentIndex - 1] << std::endl <<std::endl;
					outputBuffer[currentIndex] = 0;
					currentIndex--;
				} 
				std::cout << "Done" << std::endl;
			}
		}

		SBpoint->loadFromSamples(&outputBuffer[0], bufferSize, 1, sampleRate);

		return SBpoint;
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