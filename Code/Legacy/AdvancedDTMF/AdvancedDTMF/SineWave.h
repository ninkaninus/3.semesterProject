#pragma once
#include <vector>
#include <SFML\Audio.hpp>

class SineWave
{
public:
	SineWave(unsigned int frequency, unsigned int duration);
	SineWave(unsigned int frequency, unsigned int duration, unsigned int aSampleRate, unsigned int volume);
	virtual ~SineWave();
	unsigned int getVolume() const { return volume; };
	void setVolume(unsigned int newVolume) { volume = newVolume; };
	void generate(unsigned int freq, unsigned int durationInMs);
	std::vector<sf::Int16>& SineWave::getSamples();
protected:
	unsigned int sampleRate = 44100;
	unsigned int volume = 5000;
	double phase = 0;
	std::vector<sf::Int16> samples;
};

