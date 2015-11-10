#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include "Generator.h"
#include "Constants.h"

int main()
{

	DTMF::Generator gen;

	gen.setDuration(1.0/10);

	gen.setVolumeMax(15000);

	//gen.setTransitionMode(DTMF::Transition::zeroPadding);

	std::vector<DTMF::Tone> arr = { DTMF::Tone::ASTERISK, DTMF::Tone::HASH, DTMF::Tone::ZERO, DTMF::Tone::ONE, DTMF::Tone::TWO, DTMF::Tone::THREE, DTMF::Tone::FOUR, DTMF::Tone::FIVE, DTMF::Tone::SIX, DTMF::Tone::SEVEN, DTMF::Tone::EIGHT, DTMF::Tone::NINE, DTMF::Tone::A, DTMF::Tone::B,  DTMF::Tone::C,  DTMF::Tone::D, DTMF::Tone::ZERO, DTMF::Tone::ZERO };
	
	sf::SoundBuffer* buff = gen.generate(arr);

	sf::Sound sound;

	sound.setBuffer(*buff);

	sound.play();

	while (sound.getStatus() == sf::Sound::Playing) {

	}

	delete buff;

	return 0;
}

