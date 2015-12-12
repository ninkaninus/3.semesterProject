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
	objA.send("Hej. Hvad sker der???");
	return 0;
}
	

	


