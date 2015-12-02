#include "MyRecorder.h"

MyRecorder::MyRecorder()
{
	processingInterval = 100;
}

MyRecorder::MyRecorder(int aPInterval) :
	processingInterval(aPInterval)
{
}

bool MyRecorder::onStart() // optional
{
	// initialize whatever has to be done before the capture starts
	if (!sf::SoundRecorder::isAvailable())		
	{
		std::cout << "No Record Device Available!" << std::endl;
		return false;
	}
	sf::Time t = sf::milliseconds(processingInterval);
	sf::SoundRecorder::setProcessingInterval(t);

	// return true to start the capture, or false to cancel it
	return true;
}


bool MyRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	// do something useful with the new chunk of samples
	
	// tager de nyeste samples og tilføjer dem til bufferen

	mutex.lock();


	for (std::size_t i = 0; i < sampleCount; i++)
	{
		buffer.push_back(samples[i]);		
	}
	
	mutex.unlock();


	// return true to continue the capture, or false to stop it
	return true;
}

void MyRecorder::onStop() // optional
{
	// clean up whatever has to be done after the capture is finished

}

int MyRecorder::getBufferSize()
{
	return buffer.size();
}

std::vector<signed short> MyRecorder::getBuffer()
{
	return buffer;
}

std::vector<signed short> MyRecorder::extractBuffer()
{
	mutex.lock();

		std::vector<signed short> tempBuffer;
		tempBuffer = buffer;

		buffer.clear();

	mutex.unlock();

	return tempBuffer;
}

MyRecorder::~MyRecorder()
{
}
