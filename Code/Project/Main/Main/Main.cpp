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
	ApplicationLayer objA;
	//DataLinkReceive objD;
	//objD.init(8000, 25);

	string hej;

	PhysicalReceive Receiver;
	Receiver.init(4000, 20);

	Receiver.startRecording();
	Sleep(5000);
	Receiver.stopRecording();

	Receiver.printMagnitudes();

	//while(true)
	//{	
	//	//getline(cin, hej);
	//	//objA.send(hej);
	//	//objD.makeMessage();
	//}


	// bool to data
	//cout << objA.BooleanTodata(objA.dataToBoolean(test)) << endl;

	// Opsætningn af recieve (simulering af valid omdtaget data)
	

	
	//
	//objA.print(objD.getFrame(), "framen");

	
	// objA.print(objR.getCharInBool(),"print fra objR");
	// objA.print(objR.getCharInBool(), "print fra objR");
	

	return 0;
}
	

	


