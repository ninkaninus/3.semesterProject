#pragma once
namespace DTMF {

	static const double TWO_PI = 6.283185307179586476925286766559;

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

}
