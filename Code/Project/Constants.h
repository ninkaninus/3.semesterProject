#pragma once
#include <vector>

namespace DTMF {

	static const double TWO_PI = 6.283185307179586476925286766559;

	static const int CRCnr = 16;

	enum Tone {
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		A,
		B,
		C,
		D,
		ASTERISK,
		HASH
	};

	struct ToneFreq {
		unsigned int frequency1;
		unsigned int frequency2;
	};

	struct Frame {
		std::vector<bool> payload;
		unsigned int index;
		unsigned int maxIndex;
		unsigned int adress;
		unsigned int type;
	};

	enum transition {
		snap,
		triangle,
		steep,
		smooth
	};

}
