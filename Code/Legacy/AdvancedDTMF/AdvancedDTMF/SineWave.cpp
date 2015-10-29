#include "SineWave.h"
#include "Constants.h"

SineWave::SineWave(unsigned int aFrequency) : frequency(aFrequency) 
{

}

SineWave::SineWave(unsigned int aFrequency, double duration) : frequency(aFrequency)
{
	generate(duration);
}

SineWave::SineWave(unsigned int frequency, unsigned int duration, unsigned int aSampleRate, unsigned int aVolume) : sampleRate(aSampleRate), volume(aVolume) 
{
	generate(duration);
}

void SineWave::generateOnePeriod() {
	double period = (double(1) / frequency);
	generate(period);
}

void SineWave::generate(double duration) {
	//Something is weird with the samplefreq. Has to be twice the specified amount, to play back properly at said amount!

	double phaseAdj = (frequency * twopi) / (sampleRate * 2);

	int sampleNumb = int(duration * (sampleRate * 2));

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
