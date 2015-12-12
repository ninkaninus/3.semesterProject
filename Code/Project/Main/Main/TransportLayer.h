#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
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
		sendingData,
		receivingData,
		receivingACK,
		unInitialized
	};

public:
	TransportLayer();

	void init();

	void loop();

	void sendData();

	void sendACK();

	void receiveData();

	void receiveACK();

	void setPacket(vector<bool>*);

	vector<bool>* getPacketFromQueue();

	bool checkPacketBuffer();

	~TransportLayer();

private:

	void setState(State);
	State getState();
	unsigned int timoutACK = 2000;
	vector<bool>* currPacket;
	deque<vector<bool>*> receiveQueue;
	bool looping = true;
	State state = State::receivingData;
	DataLinkTransmit transmitter;
	DataLinkReceive receiver;
	sf::Mutex mutex;
};
