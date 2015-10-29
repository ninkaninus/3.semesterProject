<<<<<<< 0c840054aa2824bf65f44a54cb3cd071a394c077
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

	std::vector<bool> bv;

	srand(time(NULL));

	int numberOfTones = 200;

	bool value = false;

	for (int i = 0; i < 4 * numberOfTones ; i++)
	{
		value = rand() % 2;
		bv.emplace_back(value);
		std::cout << value << std::endl;
	}

	transmitter.transmit(bv);

	return 0;
}

=======
#include <SFML\Audio.hpp>

int main() {
	return 0;
}
>>>>>>> 87aad1b58824a7bb6c3e84784b7de5c63bfd8e73
