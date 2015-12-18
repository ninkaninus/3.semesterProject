#pragma once
#include <vector>

namespace DTMF {

	static const double TWO_PI = 6.283185307179586476925286766559;

	static const int CRCnr = 16;

	static const int ACKTimeout = 2;
	static const int ACKTimeoutCount = 1;
	static const float ACKResendMaxWait = 10.0;

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

	enum Type {
		Data,
		ACK
	};

	struct Frame {
		std::vector<bool> payload;
		unsigned int index;
		unsigned int address;
		Type type;
	};

	enum transition {
		snap,
		triangle,
		steep,
		smooth
	};

}
