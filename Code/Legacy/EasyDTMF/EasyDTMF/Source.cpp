#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <random>
#include <time.h>
#include "DTMFPlayer.h"
#pragma comment(lib,"Winmm.lib")
using namespace DTMF;

int main()
{

	DTMFPlayer player;

	unsigned int value = 0;

	std::vector<Tone> tones;

	srand(time(NULL));

	while (true) {

		value = rand() % (int)(65536 - 1);

		std::cout << value << " : ";

		tones = player.FromInt(value);

		for (Tone tone : tones) {
			std::cout << player.ToChar(tone);
		}

		std::cout << std::endl;

		player.PlayToneSequence(tones);

		Sleep(250);

	}
	return 0;
}