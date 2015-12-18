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

	cout << "Starter op, vent venligst!" << endl;
	ApplicationLayer objA;

	string hej;

	cout << "Klar til at sende en besked!" << endl;

	while (true)
	{
		cout << "Indtast Besked: " << std::endl;
		getline(cin, hej);
		objA.send(hej);
	}

	return 0;
}
	

	


