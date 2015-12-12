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

	setState(State::sending);

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

void TransportLayer::init() {
	loop();
}

void TransportLayer::loop() {
	while (looping) {
		if (getState() == State::sending) {
			sending();
		}

		if (getState() == State::receiving) {
			receiving();
		}
	}
}

void TransportLayer::sending() {
	DTMF::Frame frame;
	frame.payload = *currPacket;
	transmitter.transmitFrame(frame);
	setState(State::receiving);
}

void TransportLayer::receiving() {

}

TransportLayer::~TransportLayer()
{}

