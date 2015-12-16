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

	void sendACK(unsigned int ackNo);

	void setSendAllowed(bool);

	bool getSendAllowed();

	void receiveData();

	bool receiveACK();

	void sendAgainTimer();

	void setPacket(vector<bool>*);

	vector<bool>* getPacketFromQueue();

	void addPacketToQueue(vector<bool>*);

	bool checkPacketBuffer();

	~TransportLayer();

private:
	bool sendAllowed = true;
	bool getPacketAvailable();
	unsigned int timeoutACK = 5;
	unsigned int currIndex = 0;
	unsigned int expectedNext = 0;
	vector<bool>* currPacket;
	deque<vector<bool>*> receiveQueue;
	bool looping = true;
	//State state = State::receive;
	DataLinkTransmit transmitter;
	DataLinkReceive receiver;
	sf::Mutex mutex;
	unsigned const int address = 2;
};
