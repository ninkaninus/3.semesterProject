#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>

# define M_PI          3.141592653589793238462643383279502884L /* pi */

int main()
{

	if (!sf::SoundBufferRecorder::isAvailable()) {
		std::cout << "No Record Device Available!" << std::endl;
		return 0;
	}

	sf::SoundBufferRecorder recorder;

	std::cout << sf::SoundBufferRecorder::getDefaultDevice() << std::endl;

	std::cout << "Recording" << std::endl;

	recorder.start();

	Sleep(5000);

	recorder.stop();

	std::cout << "Stopped Recording" << std::endl;

	const sf::SoundBuffer& buffer = recorder.getBuffer();

	buffer.saveToFile("my_record.ogg");

	sf::Sound sound(buffer);

	sound.play();

	

	//sf::Int16* samples = buffer.getSamples();
	std::size_t count = buffer.getSampleCount();

	std::cout << "Sample count: " << count << std::endl;
	std::cout << "Sample rate: " << buffer.getSampleRate() << std::endl;

	//std::cout << goertzel(buffer.getSampleCount(), 697, 44100, )

	return 0;
}

float goertzel(int numSamples, int TARGET_FREQUENCY, int SAMPLING_RATE, float* data)
{
	int     k, i;
	float   floatnumSamples;
	float   omega, sine, cosine, coeff, q0, q1, q2, result, real, imag;

	floatnumSamples = (float)numSamples;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
	omega = (2.0 * M_PI * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i<numSamples; i++)
	{
		q0 = coeff * q1 - q2 + data[i];
		q2 = q1;
		q1 = q0;
	}
	real = (q1 - q2 * cosine);
	imag = (q2 * sine);
	result = sqrtf(real*real + imag*imag);
	return result;
}