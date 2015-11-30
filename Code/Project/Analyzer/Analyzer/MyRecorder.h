#pragma once
#include "SFML\Audio\SoundRecorder.hpp"
#include "SFML\Audio\SoundBuffer.hpp"
#include <boost\circular_buffer.hpp>
//#include "Analyzer.h"
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
	int processingInterval;
	std::vector<signed short> buffer;
	boost::circular_buffer<signed short> buffer2;
};

