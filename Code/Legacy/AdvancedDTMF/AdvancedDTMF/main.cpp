#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include "SineWave.h"

std::vector<sf::Int16> generateSine(unsigned int freq, unsigned int volume, double phase, unsigned int sampleFreq, double timeInMs);

void mix(std::vector<sf::Int16>& samples1, std::vector<sf::Int16>& samples2);

static const double twopi = 6.283185307179586476925286766559;

int main()
{

	sf::SoundBuffer buffer;

	SineWave sine(1000, 500);

	buffer.loadFromSamples(&sine.getSamples()[0], sine.getSamples().size(), 2, 44100);

	sf::Sound sound;

	sound.setBuffer(buffer);
	sound.play();

	while (sound.getStatus() == sound.Playing) {

	}

	std::cin;

	return 0;
}

void mix(std::vector<sf::Int16>& samples1, std::vector<sf::Int16>& samples2) {
	for (int i = 0; i < samples1.size(); i++) {
		samples1[i] += samples2[i];
	}
}