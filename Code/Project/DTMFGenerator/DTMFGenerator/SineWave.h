#pragma once
#include <vector>
#include <SFML\Audio.hpp>

class SineWave
{
public:
	SineWave(unsigned int aFrequency);
	SineWave(unsigned int aFrequency, double duration);
	SineWave(unsigned int afrequency, unsigned int duration, unsigned int aSampleRate, unsigned int volume);
	virtual ~SineWave();
	unsigned int getVolume() const { return volume; };
	void setVolume(unsigned int newVolume) { volume = newVolume; };
	void generate(double duration);
	void generateOnePeriod();
	std::vector<sf::Int16>& getSamples();
protected:
	unsigned int frequency;
	unsigned int sampleRate = 22050;
	unsigned int volume = 5000;
	double phase = 0;
	std::vector<sf::Int16> samples;
};

