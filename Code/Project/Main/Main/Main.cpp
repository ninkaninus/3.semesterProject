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
	//DataLinkReceive objD;
	//objD.init(8000, 20);
	//ApplicationLayer objA;
	PhysicalReceive Receiver;
	Receiver.init(8000, 25);

	Receiver.startRecording();
	//Sleep(500);
	//objA.send("Det er klart at det er tykt, når det er taaget..");
	Sleep(5000);
	Receiver.stopRecording();

	////Receiver.continuousAnalysis();
	Receiver.printMagnitudes();

	//while (true)
	//{
	//	Sleep(5000);
	//	//objD.makeFrame();
	//}

	return 0;
}
	

	


