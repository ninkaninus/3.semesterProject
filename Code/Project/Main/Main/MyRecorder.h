#pragma once
#include "SFML\Audio\SoundRecorder.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include <SFML\System\Mutex.hpp>
#include <iostream>
#include <vector>

class MyRecorder :
	public sf::SoundRecorder
{
public:
	MyRecorder();
	MyRecorder(int aPInterval);
	
	virtual bool onStart();
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	virtual void onStop();

	int getBufferSize();
	std::vector<signed short> getBuffer();
	std::vector<signed short> extractBuffer();
	~MyRecorder();

protected:
	sf::Mutex mutex;
	int processingInterval;
	std::vector<signed short> buffer;
};
