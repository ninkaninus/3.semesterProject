#include "Transmitter.h"
#include <iostream>

namespace DTMF 
{
	Transmitter::Transmitter()
	{
	}

	Transmitter::~Transmitter()
	{
	}

	void Transmitter::transmit() {

	}

	void Transmitter::transmit(std::vector<bool>& bitVector) {
		std::vector<DTMF::Tone> tones;
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

		for (DTMF::Tone t : tones) std::cout << DTMFToChar(t) << " - ";

		toneGenerator.setDuration(1.0 / 50);

		toneGenerator.setVolumeMax(15000);

		sf::SoundBuffer* buff = toneGenerator.generate(tones);

		//buff->saveToFile("DTMFSexyness.ogg");

		sf::Sound sound;

		sound.setBuffer(*buff);

		sound.play();

		while (sound.getStatus() == sf::Sound::Playing) {

		}

		delete buff;

		std::cout << "Done" << std::endl;
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

}