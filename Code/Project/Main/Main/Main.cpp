#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>


//inkludering af klasser
#include "ApplikationsLayer.h"
//#include "PhysicalRecive.h"
//#include "PhysicalTransmit.h"
//#include "DataLinkRecive.h"
//#include "DataLinkTransmit.h"
//#include "TransportLayer.h"
//#include "Transmitter/Transmitter/Transmitter.h"

using namespace std;

int main()
{
	ApplikationsLayer objA;

	string test = "Dette ";
	//objA.send("jegersejja");

	// data to bool
	cout << test << endl;
		

	// bool to data
	cout << objA.BooleanTodata(objA.dataToBoolean(test)) << endl;
	
	




	return 0;
}
	

	


