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

	transmitter.playContinousDTMF(DTMF::Tone::ONE, 5);

	transmitter.playRandomDTMF(200, 1.0 / 50.0);
	
	return 0;
}

