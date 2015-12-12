#pragma once
#include "Generator.h"
#include <vector>
#include "Constants.h"
#include <string>

namespace DTMF 
{
	class Transmitter
	{
	public:
		Transmitter();
		void transmit(std::vector<bool>&);
		void transmit(std::vector<DTMF::Tone>&);
		void setToneDuration(double);
		void setVolume(unsigned int);
		void setPreambleAmount(unsigned int);
		unsigned int getPreambleAmount() const;
		void setLogging(bool);
		bool getLogging() const;
		void playContinousDTMF(DTMF::Tone, double);
		void playRandomDTMF(int numberOfTones, double duration);
		virtual ~Transmitter();
	private:
		bool logging = false;
		std::string logFile = "DTMFTest.txt";
		void playBuffer();
		char DTMFToChar(DTMF::Tone);
		DTMF::Tone nibbleToDTMF(unsigned char c);
		Generator toneGenerator;
		sf::SoundBuffer* buffer;
		sf::Sound sound;
		int preambleAmount = 1; //One preamble set is DTMF::A and DTMF::6

	};

}

