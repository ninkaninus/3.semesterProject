#include "TransportLayer.h"
#include <Constants.h>

TransportLayer::TransportLayer()
{

}

void TransportLayer::setState(State s) {
	mutex.lock();
	state = s;
	mutex.unlock();
}

TransportLayer::State TransportLayer::getState() {
	State s;
	mutex.lock();
	s = state;
	mutex.unlock();
	return s;
}

void TransportLayer::setPacket(vector<bool>* newPacket) {
	mutex.lock();

	currPacket = newPacket;

	setState(State::sendingData);

	mutex.unlock();
}

bool TransportLayer::checkPacketBuffer() {

	bool rBool;

	mutex.lock();

	if (currPacket == nullptr) rBool = true;
	else rBool = false;

	mutex.unlock();

	return rBool;
}

vector<bool>* TransportLayer::getPacketFromQueue() {
	
	vector<bool>* ptr;
	
	mutex.lock();

	if (!receiveQueue.empty()) {
		ptr = receiveQueue[0];
		receiveQueue.pop_front();
	}
	else {
		ptr = nullptr;
	}

	mutex.unlock();

	return ptr;
}

void TransportLayer::init() {
	loop();
}

void TransportLayer::loop() {
	while (looping) {
		if (getState() == State::sendingData) {
			sendData();
		}

		if (getState() == State::receivingData) {
			receiveData();
		}
	}
}

void TransportLayer::sendData() {
	DTMF::Frame frame;
	frame.payload = *currPacket;
	transmitter.transmitFrame(frame);
	setState(State::receivingACK);
	receiveACK();
}

void TransportLayer::sendACK() {
	DTMF::Frame frame;
	frame.type = 1;
	transmitter.transmitFrame(frame);
}

void TransportLayer::receiveACK() {
	//start noget timer gøjl her

}

void TransportLayer::receiveData() {

}

TransportLayer::~TransportLayer()
{}

