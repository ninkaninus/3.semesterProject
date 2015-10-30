#pragma once
#include "Generator.h"
#include <vector>
#include "Constants.h"

namespace DTMF 
{
	class Transmitter
	{
	public:
		Transmitter();
		void transmit();
		void transmit(std::vector<bool>&);
		virtual ~Transmitter();
	private:
		char DTMFToChar(DTMF::Tone);
		DTMF::Tone nibbleToDTMF(unsigned char c);
		Generator toneGenerator;
	};