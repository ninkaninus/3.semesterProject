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
	//ApplicationLayer objA;
	DataLinkReceive objD;
	objD.init(8000, 25);

	while(true)
	{
		
		objD.makeMessage();
	}
	string test = "Dette";
	//objA.send("Hej");


	// bool to data
	//cout << objA.BooleanTodata(objA.dataToBoolean(test)) << endl;

	// Opsætningn af recieve (simulering af valid omdtaget data)
	

	
	//
	//objA.print(objD.getFrame(), "framen");

	
	// objA.print(objR.getCharInBool(),"print fra objR");
	// objA.print(objR.getCharInBool(), "print fra objR");
	

	return 0;
}
	

	


