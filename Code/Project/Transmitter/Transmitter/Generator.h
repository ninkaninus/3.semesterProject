#pragma once
#include "SFML\Audio.hpp"
#include "Constants.h"
#include <vector>

namespace DTMF 
{
	class Generator
	{

	public:
		Generator();
		void setSampleRate(unsigned int aNumber);
		unsigned int getSampleRate() const;
		void setVolumeMax(unsigned int aNumber);
		unsigned int getVolumeMax() const;
		void setDuration(double aNumber);
		double getDuration() const;
		void setVolumeSmoothing(bool);
		bool getVolumeSmoothing() const;
		sf::SoundBuffer* generate(std::vector<bool>);
		sf::SoundBuffer* generate(std::vector<DTMF::Tone>);
		virtual ~Generator();
	protected:
		bool volumeSmoothing = true;
		DTMF::ToneFreq getFreq(DTMF::Tone);
		unsigned int sampleRate = 8000;
		unsigned int volumeMax = 15000;
		double duration = 0.1;
	};

}

