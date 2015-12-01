#pragma once
#include "Generator.h"
#include <vector>
#include "Constants.h"

namespace DTMF 
{
	class Transmitter
	{
	public:
		Transmitter();
		void transmit();
		void transmit(std::vector<bool>&);
		void setToneDuration(double);
		void setVolume(unsigned int);
		void playContinousDTMF(DTMF::Tone, double);
		void playRandomDTMF(int numberOfTones, double duration);
		virtual ~Transmitter();
	private:
		void playBuffer();
		char DTMFToChar(DTMF::Tone);
		DTMF::Tone nibbleToDTMF(unsigned char c);
		Generator toneGenerator;
		sf::SoundBuffer* buffer;
		sf::Sound sound;

	};

}

