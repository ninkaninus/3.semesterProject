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
/*
	ApplicationLayer objA;

	string hej;

	while (true)
	{
		getline(cin, hej);
		objA.send(hej);
	}
*/

	PhysicalReceive receiver;
	receiver.startRecording();
	Sleep(5000);
	receiver.stopRecording();

	receiver.printMagnitudes();

	return 0;
}
	

	


