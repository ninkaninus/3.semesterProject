#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include "Generator.h"
#include "Transmitter.h"
#include "Constants.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

	DTMF::Transmitter transmitter;

	transmitter.setToneDuration(5);

	transmitter.playContinousDTMF(DTMF::Tone::ONE);

	transmitter.setToneDuration(1.0 / 50);

	std::vector<bool> bv;

	srand(time(NULL));

	int numberOfTones = 200;

	bool value = false;

	bv.push_back(1);
	bv.push_back(0);
	bv.push_back(1);
	bv.push_back(0);
	bv.push_back(0);
	bv.push_back(1);
	bv.push_back(1);
	bv.push_back(0);

	for (int i = 0; i < 4 * numberOfTones ; i++)
	{
		value = rand() % 2;
		bv.push_back(value);
		//std::cout << value << std::endl;
	}

	transmitter.transmit(bv);
	
	return 0;
}

