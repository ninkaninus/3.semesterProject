#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <Windows.h>


//inkludering af klasser
#include "ApplicationLayer.h"
#include "DataLinkReceive.h"

using namespace std;

int main()
{
	PhysicalReceive Receiver;
	Receiver.init(8000, 25);

	Receiver.startRecording();
	Sleep(2000);

	std::thread analysis(&PhysicalReceive::continuousAnalysis, &Receiver);
	analysis.detach();

	while(true)
	{
		//Sleep(5000);
		//objD.makeFrame();
	}


	return 0;
}
	

	


