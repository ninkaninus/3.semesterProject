#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <Windows.h>


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

	objA.send("Mr. Watson, come here, I want to see you!");
	
	Sleep(1000);
}