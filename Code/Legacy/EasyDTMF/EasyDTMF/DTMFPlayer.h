#pragma once
#include <string>
#include <vector>
namespace DTMF {

	enum Tone { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D, STAR, NUMBER};

	class DTMFPlayer
	{
	public:
		DTMFPlayer();
		virtual ~DTMFPlayer();
		void PlayTone(Tone tone) const;
		void PlayToneSequence(std::vector<Tone> tones) const;
		char ToChar(Tone d) const;
		Tone FromChar(char c) const;
		std::vector<Tone> FromInt(signed int input) const;
		std::vector<Tone> FromString(std::string input) const;
	protected:
		Tone FromNibble(char n) const;	//Somewhat odd function. Assumes that the nibble you want converted to DTMF is stored in the lower 4 bits of the char. Only used as a helper function for Integer conversion.
	};

}

