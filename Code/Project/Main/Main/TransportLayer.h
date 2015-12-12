#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <chrono>
#include <thread>
#include "DataLinkTransmit.h"
#include "DataLinkReceive.h"
#include <SFML\System\Mutex.hpp>

class TransportLayer
{
	enum State {
		sending,
		receiving,
		unInitialized
	};

public:
	TransportLayer();

	void init();

	void loop();

	void sending();

	void receiving();

	void setPacket(vector<bool>*);

	bool checkPacketBuffer();

	~TransportLayer();

private:

	void setState(State);
	State getState();

	vector<bool>* currPacket;
	bool looping = true;
	State state = State::sending;
	DataLinkTransmit transmitter;
	DataLinkReceive receiver;
	sf::Mutex mutex;
};
