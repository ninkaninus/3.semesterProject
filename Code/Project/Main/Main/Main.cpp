#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <Windows.h>

//inkludering af klasser
#include "ApplicationLayer.h"
#include "DataLinkReceive.h"
#include "Transmitter\Transmitter\Transmitter.h"

using namespace std;

int main()
{
	DataLinkReceive receiver;

	//receiver.init(8000, 25);

	while (true)
	{

	}

	DTMF::Transmitter transmitter;
	//transmitter.playRandomDTMF(200, 25.0 / 1000);

	return 0;
}
	

	


