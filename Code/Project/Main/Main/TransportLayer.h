#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <random>
#include <bitset>
#include <thread>
#include "DataLinkTransmit.h"
#include "DataLinkReceive.h"
#include <SFML\System\Mutex.hpp>

class TransportLayer
{
	/*
	enum State {
		sendingData,
		receive,
		receivingACK,
		unInitialized
	};
	*/

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

	void setPacketAvailable(bool);
	bool getPacketAvailable();
	bool packetAvailable = false;
	unsigned int timeoutACK = 2;
	vector<bool>* currPacket;
	deque<vector<bool>*> receiveQueue;
	bool looping = true;
	//State state = State::receive;
	DataLinkTransmit transmitter;
	DataLinkReceive receiver;
	sf::Mutex mutex;
};
