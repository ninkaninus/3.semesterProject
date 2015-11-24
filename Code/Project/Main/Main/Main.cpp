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
#include "Transmitter/Transmitter/Transmitter.h"

using namespace std;

int main()
{

	DataLinkTransmit objD;
	TransportLayer objT;
	ApplikationsLayer objA;
	DTMF::Transmitter objTransmit;

	objA.dataToBoolean("hejhejhejhejhejhejhejhejddddddddddddddddddddddddhej");

	objT.newInput(objA.returnData());
	
	objT.getPayload(0);
	objD.assembleFrame(objT.returnPayload(), 0, objT.returnMaxIndex());
	objTransmit.transmit(objD.returnPayload());

	objT.getPayload(1);
	objD.assembleFrame(objT.returnPayload(), 1, 16);
	objTransmit.transmit(objD.returnPayload());


}