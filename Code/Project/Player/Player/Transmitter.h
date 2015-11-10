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
		void Transmit();
		void transmit(std::vector<bool>&);
		virtual ~Transmitter();
	private:
		Generator toneGenerator;
	};

}

