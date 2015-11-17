#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <bitset>

using namespace std;


class ApplikationsLayer
{
public:
	ApplikationsLayer();				
	void interfaceUpdate();				//eventuel understyttelse af UserInterface
	void xToData(string input);			//konverter fra input til vektor af bytes
	void dataToX();						//konverter fra vektor af bytes til output
	void dataTypeExtract();				//hvilken datatype der skal sende
	void send(vector<bool>& iVector);	//sender input
	void dataToBoolean(string aString); // konverterer indkommen data til bool
	vector<bool> returnData();

	~ApplikationsLayer();

protected:
	bool sendStatus;					//Er beskeden nået frem og klar til at sende igen
	vector<bool> data;					//Den konverterede datastreng som skal sendes
	string input;						//Hvad en bruger vil sende
	int dataType;						//Her bruger vi et nummer til at indikere hvilken datatype der er tale om
};

