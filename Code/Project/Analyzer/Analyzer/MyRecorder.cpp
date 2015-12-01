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
	
	buffer2.set_capacity(100000);

	// return true to start the capture, or false to cancel it
	return true;
}


bool MyRecorder::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	// do something useful with the new chunk of samples
	
	// tager de nyeste samples og tilføjer dem til bufferen
	for (std::size_t i = 0; i < sampleCount; i++)
	{
		buffer2.push_back(samples[i]);		
	}
		
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
	std::vector<signed short> tempBuffer;
	boost::circular_buffer<signed short> temp = buffer2;
	//tempBuffer = buffer;
	
	for (std::size_t i = 0; i < temp.size(); i++)
	{
		tempBuffer.push_back(buffer2[i]);
	}

	buffer2.erase(buffer2.begin(), buffer2.begin() + tempBuffer.size());

	//buffer.erase(buffer.begin(), buffer.begin() + tempBuffer.size());

	return tempBuffer;
}

MyRecorder::~MyRecorder()
{
}
