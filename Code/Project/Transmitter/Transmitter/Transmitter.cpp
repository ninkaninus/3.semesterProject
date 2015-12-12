#include "Transmitter.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

namespace DTMF 
{
	Transmitter::Transmitter()
	{
		setToneDuration(25.0/1000);
		setVolume(15000);
	}

	Transmitter::~Transmitter()
	{
		delete buffer;
	}

	void Transmitter::setLogging(bool b) {
		logging = b;
	}

	bool Transmitter::getLogging() const {
		return logging;
	}

	void Transmitter::transmit(std::vector<DTMF::Tone>& tones) {
		buffer = toneGenerator.generate(tones);
		playBuffer();
	}

	void Transmitter::transmit(std::vector<bool>& bitVector) {
		std::vector<DTMF::Tone> tones; 
		for (int i = 0; i < preambleAmount; i++) {
			tones.push_back(DTMF::Tone::A);
			tones.push_back(DTMF::Tone::SIX);
		}
		unsigned char nibble = 0;
		int count = 3;
		for (bool b : bitVector) 
		{
			nibble = nibble | (b << count);
			count--;
			if (count < 0) 
			{
				count = 3;
				tones.emplace_back(nibbleToDTMF(nibble));
				nibble = 0;
			}
		}

		if (logging == true) {
			std::ofstream myFile;
			myFile.open(logFile);
			for (DTMF::Tone tone : tones) {
				myFile << DTMFToChar(tone);
			}
			myFile.close();
		}

		buffer = toneGenerator.generate(tones);
		playBuffer();
	}

	void Transmitter::playContinousDTMF(DTMF::Tone tone, double duration) {

		double prevDuration = toneGenerator.getDuration();

		toneGenerator.setDuration(duration);

		std::vector<DTMF::Tone> tones;

		tones.push_back(tone);

		bool smoothingTemp = toneGenerator.getVolumeSmoothing();

		toneGenerator.setVolumeSmoothing(false);

		buffer = toneGenerator.generate(tones);

		playBuffer();

		toneGenerator.setVolumeSmoothing(smoothingTemp);

		toneGenerator.setDuration(prevDuration);
	}

	void Transmitter::playRandomDTMF(int numberOfTones, double duration) {

		double prevDuration = toneGenerator.getDuration();

		toneGenerator.setDuration(duration);

		std::vector<bool> bv;

		srand(time(NULL));

		bool value;

		for (int i = 0; i < 4 * numberOfTones; i++)
		{
			value = rand() % 2;
			bv.push_back(value);
			//std::cout << value << std::endl;
		}

		transmit(bv);

		toneGenerator.setDuration(prevDuration);
	}

	void Transmitter::playBuffer() {
		sound.setBuffer(*buffer);
		sound.play();

		while (sound.getStatus() == sf::Sound::Playing) {

		}

		Sleep(1000);
	}

	DTMF::Tone Transmitter::nibbleToDTMF(unsigned char c) {
		switch (c)
		{
		case 0:
			return DTMF::Tone::ZERO;
		case 1:
			return DTMF::Tone::ONE;
		case 2:
			return DTMF::Tone::TWO;
		case 3:
			return DTMF::Tone::THREE;
		case 4:
			return DTMF::Tone::FOUR;
		case 5:
			return DTMF::Tone::FIVE;
		case 6:
			return DTMF::Tone::SIX;
		case 7:
			return DTMF::Tone::SEVEN;
		case 8:
			return DTMF::Tone::EIGHT;
		case 9:
			return DTMF::Tone::NINE;
		case 10:
			return DTMF::Tone::A;
		case 11:
			return DTMF::Tone::B;
		case 12:
			return DTMF::Tone::C;
		case 13:
			return DTMF::Tone::D;
		case 14:
			return DTMF::Tone::ASTERISK;
		case 15:
			return DTMF::Tone::HASH;
		default:
			std::cerr << "NIBBLE NO GOOD" << std::endl;
			break;
		}
	}

	char Transmitter::DTMFToChar(DTMF::Tone t) {
		switch (t)
		{
		case DTMF::ZERO:
			return '0';
		case DTMF::ONE:
			return '1';
		case DTMF::TWO:
			return '2';
		case DTMF::THREE:
			return '3';
		case DTMF::FOUR:
			return '4';
		case DTMF::FIVE:
			return '5';
		case DTMF::SIX:
			return '6';
		case DTMF::SEVEN:
			return '7';
		case DTMF::EIGHT:
			return '8';
		case DTMF::NINE:
			return '9';
		case DTMF::A:
			return 'A';
		case DTMF::B:
			return 'B';
		case DTMF::C:
			return 'C';
		case DTMF::D:
			return 'D';
		case DTMF::ASTERISK:
			return '*';
		case DTMF::HASH:
			return '#';
		default:
			std::cerr << "YOU DONE GOOFED" << std::endl;
		}
	}

	void Transmitter::setToneDuration(double duration) {
		toneGenerator.setDuration(duration);
	}

	void Transmitter::setVolume(unsigned int vol) {
		toneGenerator.setVolumeMax(vol);
	}

	void Transmitter::setPreambleAmount(unsigned int amount) {
		preambleAmount = amount;
	}

	unsigned int Transmitter::getPreambleAmount() const {
		return preambleAmount;
	}

}