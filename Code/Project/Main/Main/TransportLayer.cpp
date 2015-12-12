#include "TransportLayer.h"
#include <Constants.h>
#include <iostream>
#include <chrono>
#include <thread>

TransportLayer::TransportLayer()
{
	std::thread launch(&TransportLayer::init, this);
	launch.detach();
}


void TransportLayer::setPacketAvailable(bool b) 
{
	mutex.lock();
	packetAvailable = b;
	mutex.unlock();
}

bool TransportLayer::getPacketAvailable() 
{
	bool b;
	mutex.lock();
	b = packetAvailable;
	mutex.unlock();
	return b;
}


void TransportLayer::setPacket(vector<bool>* newPacket) 
{
	mutex.lock();

	currPacket = newPacket;

	setPacketAvailable(true);

	mutex.unlock();
}

bool TransportLayer::checkPacketBuffer() 
{

	bool rBool;

	mutex.lock();

	if (currPacket == nullptr) rBool = true;
	else rBool = false;

	mutex.unlock();

	return rBool;
}

vector<bool>* TransportLayer::getPacketFromQueue() 
{
	vector<bool>* ptr;
	
	mutex.lock();

	if (!receiveQueue.empty()) 
	{
		ptr = receiveQueue[0];
		receiveQueue.pop_front();
	}
	else 
	{
		ptr = nullptr;
	}

	mutex.unlock();

	return ptr;
}

void TransportLayer::init() 
{
	//receiveACK();
	loop();
}

void TransportLayer::loop() 
{
	while (looping) 
	{
		if (getPacketAvailable()) 
		{
			sendData();
		}
		else 
		{
			receiveData();
		}
	}
}

void TransportLayer::sendData() 
{
	DTMF::Frame frame;
	frame.payload = *currPacket;
	delete currPacket;
	currPacket = nullptr;
	setPacketAvailable(false);
	std::cout << "Sending Frame" << std::endl;
	transmitter.transmitFrame(frame);
	receiveACK();

}

void TransportLayer::sendACK() 
{
	DTMF::Frame frame;
	frame.type = 1;
	transmitter.transmitFrame(frame);
}

void TransportLayer::receiveACK() 
{
	auto endTimePoint = std::chrono::system_clock::now();
	auto startTimePoint = std::chrono::system_clock::now();
	std::chrono::duration<float> diffTimePoint;
	float timeDifference = 0;

	//start timer
<<<<<<< af314a2b23b29252eb17e4fab29f661536cf09a5
	//std::cout << "Start!" << std::endl;
=======
	std::cout << "Start!" << std::endl;
>>>>>>> f7bb712cf114907716fb4a37da67a2037ecfc345
	startTimePoint = std::chrono::system_clock::now();

	while (timeDifference < timeoutACK) 
	{
		endTimePoint = std::chrono::system_clock::now();
		diffTimePoint = endTimePoint - startTimePoint;
		timeDifference = diffTimePoint.count();
	}
	//std::cout << timeDifference << " seconds went by with no ACK!" << std::endl;

	//We assume ack was received here, untill it is implemented


}

void TransportLayer::receiveData() 
{
	//Check if there is data in the datalinkreceiver buffer
}

TransportLayer::~TransportLayer()
{}

