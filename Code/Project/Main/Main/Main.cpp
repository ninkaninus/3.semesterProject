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

	DataLinkReceive objA;

	string hej;

	while (true)
	{
		getline(cin, hej);
		//objA.send(hej);
	}

	return 0;
}
	

	


