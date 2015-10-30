#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include "Generator.h"
#include "Constants.h"

/*
std::vector<sf::Int16> generateSine(unsigned int freq, unsigned int volume, double phase, unsigned int sampleFreq, double timeInMs);

void mix(std::vector<sf::Int16>& samples1, std::vector<sf::Int16>& samples2);
*/

int main()
{

	DTMF::Generator gen;

	gen.setDuration(1.0/12.5);

	gen.setVolume(15000);

	std::vector<DTMF::Tone> arr = { DTMF::Tone::ZERO, DTMF::Tone::ONE, DTMF::Tone::TWO, DTMF::Tone::THREE, DTMF::Tone::FOUR, DTMF::Tone::FIVE, DTMF::Tone::SIX, DTMF::Tone::SEVEN, DTMF::Tone::EIGHT, DTMF::Tone::NINE, DTMF::Tone::A, DTMF::Tone::B,  DTMF::Tone::C,  DTMF::Tone::D, DTMF::Tone::ASTERISK, DTMF::Tone::HASH };
	
	sf::SoundBuffer* buff = gen.generate(arr);

	sf::Sound sound;

	sound.setBuffer(*buff);

	sound.play();

	while (sound.getStatus() == sf::Sound::Playing) {

	}

	delete buff;

	return 0;
}

