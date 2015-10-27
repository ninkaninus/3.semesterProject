#include "DTMFPlayer.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
namespace DTMF {

	DTMFPlayer::DTMFPlayer()
	{
	}

	//Requires you to have the correctly named .wav files in the same directory as the code. Or else it will just play standard windows error sound.
	void DTMFPlayer::PlayTone(Tone tone) const {
		switch (tone)
		{
		case ZERO:
			PlaySound(L"DTMF0.wav", NULL, SND_FILENAME);
			break;
		case ONE:
			PlaySound(L"DTMF1.wav", NULL, SND_FILENAME);
			break;
		case TWO:
			PlaySound(L"DTMF2.wav", NULL, SND_FILENAME);
			break;
		case THREE:
			PlaySound(L"DTMF3.wav", NULL, SND_FILENAME);
			break;
		case FOUR:
			PlaySound(L"DTMF4.wav", NULL, SND_FILENAME);
			break;
		case FIVE:
			PlaySound(L"DTMF5.wav", NULL, SND_FILENAME);
			break;
		case SIX:
			PlaySound(L"DTMF6.wav", NULL, SND_FILENAME);
			break;
		case SEVEN:
			PlaySound(L"DTMF7.wav", NULL, SND_FILENAME);
			break;
		case EIGHT:
			PlaySound(L"DTMF8.wav", NULL, SND_FILENAME);
			break;
		case NINE:
			PlaySound(L"DTMF9.wav", NULL, SND_FILENAME);
			break;
		case A:
			PlaySound(L"DTMFA.wav", NULL, SND_FILENAME);
			break;
		case B:
			PlaySound(L"DTMFB.wav", NULL, SND_FILENAME);
			break;
		case C:
			PlaySound(L"DTMFC.wav", NULL, SND_FILENAME);
			break;
		case D:
			PlaySound(L"DTMFD.wav", NULL, SND_FILENAME);
			break;
		case STAR:
			PlaySound(L"DTMFStar.wav", NULL, SND_FILENAME);
			break;
		case NUMBER:
			PlaySound(L"DTMF#.wav", NULL, SND_FILENAME);
			break;
		default:
			break;
		}
	}

	char DTMFPlayer::ToChar(Tone d) const {
		switch (d)
		{
		case Tone::A:
			return 'A';
		case Tone::B:
			return 'B';
		case Tone::C:
			return 'C';
		case Tone::D:
			return 'D';
		case Tone::ZERO:
			return '0';
		case Tone::ONE:
			return '1';
		case Tone::TWO:
			return '2';
		case Tone::THREE:
			return '3';
		case Tone::FOUR:
			return '4';
		case Tone::FIVE:
			return '5';
		case Tone::SIX:
			return '6';
		case Tone::SEVEN:
			return '7';
		case Tone::EIGHT:
			return '8';
		case Tone::NINE:
			return '9';
		case Tone::STAR:
			return '*';
		case Tone::NUMBER:
			return '#';
		default:
			return '-';
		}
	}

	//No exception handling code yet as the default argument!
	Tone DTMFPlayer::FromChar(char c) const {
		switch (c)
		{
		case 'a' | 'A':
			return Tone::A;
		case 'b' | 'B':
			return Tone::B;
		case 'c' | 'C':
			return Tone::C;
		case 'd' | 'D':
			return Tone::D;
		case '0':
			return Tone::ZERO;
		case '1':
			return Tone::ONE;
		case '2':
			return Tone::TWO;
		case '3':
			return Tone::THREE;
		case '4':
			return Tone::FOUR;
		case '5':
			return Tone::FIVE;
		case '6':
			return Tone::SIX;
		case '7':
			return Tone::SEVEN;
		case '8':
			return Tone::EIGHT;
		case '9':
			return Tone::NINE;
		case '*':
			return Tone::STAR;
		case '#':
			return Tone::NUMBER;
		default:
			break;
		}
	}

	Tone DTMFPlayer::FromNibble(char n) const {
		switch (n)
		{
		case 0:
			return Tone::ZERO;
		case 1:
			return Tone::ONE;
		case 2:
			return Tone::TWO;
		case 3:
			return Tone::THREE;
		case 4:
			return Tone::FOUR;
		case 5:
			return Tone::FIVE;
		case 6:
			return Tone::SIX;
		case 7:
			return Tone::SEVEN;
		case 8:
			return Tone::EIGHT;
		case 9:
			return Tone::NINE;
		case 10:
			return Tone::A;
		case 11:
			return Tone::B;
		case 12:
			return Tone::C;
		case 13:
			return Tone::D;
		case 14:
			return Tone::STAR;
		case 15:
			return Tone::NUMBER;
		default:
			break;
		}
	}

	std::vector<Tone> DTMFPlayer::FromInt(signed int input) const {
		std::vector<Tone> tones;
		unsigned char shifted = 0;
		for (int i = 0; i < 4; i++) {
			shifted = input >> (4 * i);
			shifted &= 0x0F;
			tones.emplace_back(FromNibble(shifted));
		}
		return tones;
	}

	//No exception handling code yet! Only input strings consisting of valid DTMF tones!
	std::vector<Tone> DTMFPlayer::FromString(std::string input) const {
		std::vector<Tone> tones;
		Tone d;
		for (char c : input) {
			d = FromChar(c);
			tones.emplace_back(d);
		}
		return tones;
	}

	void DTMFPlayer::PlayToneSequence(std::vector<Tone> tones) const {
		for (Tone tone : tones) {
			PlayTone(tone);
		}
	}

	DTMFPlayer::~DTMFPlayer()
	{
	}

}
