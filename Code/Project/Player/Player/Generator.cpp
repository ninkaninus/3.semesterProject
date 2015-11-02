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

	unsigned int Generator::getVolume() const 
	{
		return volume;
	}

	void Generator::setVolume(unsigned int aNumber) 
	{
		volume = aNumber;
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

		for (int i = 0; i < toneBuffer.size(); i++) 
		{
			phase1 = 0;
			phase2 = 0;

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
					if (std::abs(outputBuffer[currentIndex - 1]) < std::abs(outputBuffer[currentIndex])) peaked = true;
					else outputBuffer[currentIndex] = 0;

				} while (peaked == false);

				while(std::abs(outputBuffer[currentIndex - 1]) < std::abs(outputBuffer[currentIndex]))
				{
					outputBuffer[currentIndex] = 0;
				} 
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