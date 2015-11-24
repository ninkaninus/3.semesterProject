#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>

//inkludering af klasser
#include "PhysicalRecive.h"
#include "PhysicalTransmit.h"
#include "DataLinkRecive.h"
#include "DataLinkTransmit.h"
#include "TransportLayer.h"
#include "ApplikationsLayer.h"


using namespace std;

int main()
{

	DataLinkTransmit objD;
	TransportLayer objT;
	ApplikationsLayer objA;



	objA.dataToBoolean("hej");

	objT.newInput(objA.returnData());
	objT.getPayload(0);
	
	objD.assembleFrame(objT.returnPayload(), 0, 0);

	objD.printFrames();

}