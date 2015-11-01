#pragma once
#include "SFML\Audio.hpp"
#include "Constants.h"
#include <vector>

namespace DTMF 
{

	enum Transition
	{
		instant,
		linear,
		smooth,
		flat,
		zeroPadding
	};

	class Generator
	{

	public:
		Generator();
		void setSampleRate(unsigned int aNumber);
		unsigned int getSampleRate() const;
		void setVolume(unsigned int aNumber);
		unsigned int getVolume() const;
		void setDuration(double aNumber);
		double getDuration() const;
		void setTransitionMode(Transition);
		Transition getTransitionMode() const;
		sf::SoundBuffer* generate(std::vector<DTMF::Tone>);
		virtual ~Generator();
	protected:
		DTMF::ToneFreq getFreq(DTMF::Tone);
		unsigned int sampleRate = 8000;
		unsigned int volume = 5000;
		double duration = 1;
		Transition transition = Transition::instant;
	};

}

