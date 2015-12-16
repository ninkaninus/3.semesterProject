#include <SFML/Audio.hpp>
#include <iostream>
#include "Generator.h"
#include "Transmitter.h"
#include <Constants.h>
#include <vector>

int main()
{
	DTMF::Transmitter transmitter;

	//transmitter.playContinousDTMF(DTMF::Tone::ONE, 5);

	transmitter.setLogging(true);

	transmitter.playRandomDTMF(300, 25.0 / 1000);

	/*
	std::vector<DTMF::Tone> tones = { DTMF::Tone::ZERO, DTMF::Tone::ONE, DTMF::Tone::TWO, DTMF::Tone::THREE, DTMF::Tone::FOUR, DTMF::Tone::FIVE, DTMF::Tone::SIX, DTMF::Tone::SEVEN, DTMF::Tone::EIGHT, DTMF::Tone::NINE, DTMF::Tone::A, DTMF::Tone::B, DTMF::Tone::C, DTMF::Tone::D, DTMF::Tone::ASTERISK, DTMF::Tone::HASH };

	transmitter.setToneDuration(25 / 1000.0 );
	transmitter.transmit(tones);
	*/

	return 0;
}

