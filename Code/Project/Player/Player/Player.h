#pragma once
#include <vector>
#include <SFML/Audio.hpp>

namespace DTMF {

	static enum  Tone {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, A, B, C, D, Asterisk, Hash};

	class Player
	{
	public:
		Player();
		int getSampleRate() const { return sampleRate; };
		void setSampleRate(int newSampleRate) { sampleRate = newSampleRate; };
		virtual ~Player();
	protected:
		unsigned int sampleRate = 44100;
	};
}

