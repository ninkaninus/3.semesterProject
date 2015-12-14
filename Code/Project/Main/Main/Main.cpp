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

void compareFiles() {
	ifstream Received("CharsReceived.txt");

	string charsReceived;

	while (Received.good())
	{
		charsReceived += Received.get();
	}

	ifstream Sent("CharsSent.txt");

	string charsSent;

	while (Sent.good())
	{
		charsSent += Sent.get();
	}
	
	int lengthReceived = charsReceived.size();
	int lengthSent = charsSent.size();

	if (lengthReceived == lengthSent)
	{
		int errorCount = 0;

		for (unsigned int i = 0; i < lengthReceived; i++)
		{
			if (charsReceived[i] != charsSent[i])
				errorCount++;
		}

		double percentage = double(errorCount) / double(lengthReceived);

		cout << "Found " << errorCount << " errors in " << lengthReceived << " characters" << endl;
		cout << "Received differs from sent by: " << percentage << " %" << endl;
	}
	else
	{
		cout << "Sent " << lengthSent << " characters" << endl;
		cout << "Received " << lengthReceived << " characters" << endl;
	}
		 
}

int main()
{

	ApplicationLayer objA;

	string hej;

	while (true)
	{
		getline(cin, hej);
		objA.send(hej);
		getline(cin, hej);
		compareFiles();
	}

	return 0;
}
	

	


