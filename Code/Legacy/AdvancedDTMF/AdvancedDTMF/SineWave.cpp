#include "SineWave.h"
#include "Constants.h"

SineWave::SineWave(unsigned int frequency, unsigned int duration)
{
	generate(frequency, duration);
}

SineWave::SineWave(unsigned int frequency, unsigned int duration, unsigned int aSampleRate, unsigned int aVolume) : sampleRate(aSampleRate), volume(aVolume) 
{
	generate(frequency, duration);
}

void SineWave::generate(unsigned int freq, unsigned int durationInMs) {
	//Something is weird with the samplefreq. Has to be twice the specified amount, to play back properly at said amount!

	double phaseAdj = (freq * twopi) / (sampleRate * 2);

	int sampleNumb = int(durationInMs * ((sampleRate * 2) / 1000));

	for (int i = 0; i < sampleNumb; ++i)
	{
		samples.emplace_back(static_cast<sf::Int16>(volume * (std::sin(phase))));

		phase += phaseAdj;

		if (phase >= twopi) phase -= twopi;
	}
}

std::vector<sf::Int16>& SineWave::getSamples() {
	return samples;
}

SineWave::~SineWave()
{
}
