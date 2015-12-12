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

using namespace std;

class TransportLayer
{
public:
	TransportLayer();

	~TransportLayer();

private:
	DataLinkTransmit transmitter;
	DataLinkReceive receiver;
	sf::Mutex mutex;
};
