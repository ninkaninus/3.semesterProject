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

bool TransportLayer::getPacketAvailable() 
{
	bool b = false;
	mutex.lock();
	if (currPacket) b = true;
	mutex.unlock();
	return b;
}

void TransportLayer::setPacket(vector<bool>* newPacket) 
{
	mutex.lock();

	currPacket = newPacket;

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

void TransportLayer::addPacketToQueue(vector<bool>* b)
{
	mutex.lock();
		receiveQueue.push_back(b);
	mutex.unlock();
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

		receiveData();
	}
}

void TransportLayer::sendData() 
{
	DTMF::Frame frame;
	frame.payload = *currPacket;
	frame.address = address;
	frame.index = currIndex;
	frame.type = DTMF::Type::Data;
	delete currPacket;
	currPacket = nullptr;
	//std::cout << "Sending Frame" << std::endl;
	transmitter.transmitFrame(frame);
	while(!receiveACK()) {
		transmitter.transmitFrame(frame);
	}
}

bool TransportLayer::receiveACK() 
{
	auto endTimePoint = std::chrono::system_clock::now();
	auto startTimePoint = std::chrono::system_clock::now();
	std::chrono::duration<float> diffTimePoint;
	float timeDifference = 0;

	//start timer

	//std::cout << "Start!" << std::endl;
	startTimePoint = std::chrono::system_clock::now();

	while (timeDifference < timeoutACK) 
	{
		endTimePoint = std::chrono::system_clock::now();
		diffTimePoint = endTimePoint - startTimePoint;
		timeDifference = diffTimePoint.count();

		if (receiver.checkFrame())
		{
			DTMF::Frame fPoint = receiver.getFrame();

			if (fPoint.type == DTMF::Type::ACK && fPoint.index == currIndex)
			{
				if (currIndex == 0) currIndex = 1;
				else currIndex = 0;
				return true;
			}
		}
	}

	std::cout << timeDifference << " seconds went by with no ACK!" << std::endl;
	//We assume ack was received here, untill it is implemented
	return false;
}

void TransportLayer::receiveData() 
{
	if (receiver.checkFrame())
	{
		DTMF::Frame fPoint = receiver.getFrame();
		if (fPoint.type == DTMF::Type::Data)
		{
			sendACK(fPoint.index);
			if (fPoint.index == expectedNext)
			{
				if (expectedNext == 0) expectedNext = 1;
				else expectedNext = 0;
				vector<bool>* point = new vector<bool>;
				*point = fPoint.payload;
				addPacketToQueue(point);
			}
		}
	}
}

void TransportLayer::sendACK(unsigned int ackNo)
{
	DTMF::Frame frame;
	frame.type = DTMF::Type::ACK;
	frame.index = ackNo;
	transmitter.transmitFrame(frame);
}

TransportLayer::~TransportLayer()
{}

