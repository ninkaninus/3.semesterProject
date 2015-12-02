#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <Windows.h>


//inkludering af klasser
#include "ApplikationsLayer.h"
#include "PhysicalRecive.h"
//#include "PhysicalTransmit.h"
#include "DataLinkRecive.h"
//#include "DataLinkTransmit.h"
//#include "TransportLayer.h"
//#include "Transmitter/Transmitter/Transmitter.h"

using namespace std;

int main()
{
	ApplikationsLayer objA;
	DataLinkRecive objD;

	string test = "Dette";
	//objA.send("Hej");


	// bool to data
	cout << objA.BooleanTodata(objA.dataToBoolean(test)) << endl;

	// Opsætningn af recieve (simulering af valid omdtaget data)
	

	
	objD.makeFrame();
	//objA.print(objD.getFrame(), "framen");

	
	// objA.print(objR.getCharInBool(),"print fra objR");
	// objA.print(objR.getCharInBool(), "print fra objR");
	

	return 0;
}
	

	


