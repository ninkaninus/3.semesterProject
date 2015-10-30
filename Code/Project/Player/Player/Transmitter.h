#pragma once
#include "Generator.h"
#include <vector>
#include "Constants.h"

namespace DTMF {
	class Transmitter
	{
	public:
		Transmitter();
		void Transmit(std::vector<int>);
		virtual ~Transmitter();
	private:
		Generator toneGenerator;
	};

}

