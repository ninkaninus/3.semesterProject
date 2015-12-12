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
	DataLinkReceive objD;

	//objA.send("Penis");
	objD.init(8000,25);

	while (true) {
		Sleep(5000);
		objD.makeMessage();
	}
	

	return 0;
}
	

	


