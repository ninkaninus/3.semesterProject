#include "DataLinkRecive.h"
#include <iostream>


DataLinkRecive::DataLinkRecive()
{
	//dette er til test
	vector<bool> sim = { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 };
	objR.setCharInBool(sim);
}

void DataLinkRecive::makeFrame()
{
	// Opsætning 
	Frame newFrame;
	vector<bool> frame = objR.extractBoolVector();
	

	// Tilføje bools til data vectoren 
	for (bool i : frame)
		data.push_back(i);
	frame.clear();


	// Find næste frame af data
	int aFlag = 0;
	int length = 0;

	for (unsigned int i = 7; i < data.size(); i++)
	{

		// Led efter flag
		if (!data[i - 1] && data[i - 2] && data[i - 3] && data[i - 4] && data[i - 5] && data[i - 6] && data[i - 7] && !data[i - 8]) {
			//en frame er begyndt
			aFlag++;
		}

		
		// tilføj data uden frame 
		if (aFlag == 1)
			frame.push_back(data[i]);


		//stop hvis der et nyt flag
		if (aFlag > 1) {
			break;

		}			
	}
	
	for (int i = 0; i < 8; i++) {
		frame.pop_back();
	}

	// Fjern denne frame fra data
	
	for (unsigned int i = 0; i < frame.size() +16; i++)


	// Flag skal indholdet valideres


	// Består den testen returneres payload ellers returneres en tom vektor

}

Frame DataLinkRecive::getFrame()
{
	Frame temp = toTrans[0];
	toTrans.pop_front();
	return temp;
}

unsigned int DataLinkRecive::numberOfFrames()
{
	return toTrans.size();
}


DataLinkRecive::~DataLinkRecive()
{
}

void DataLinkRecive::print(vector<bool>& aVector, string aName)
{
	cout << endl << "dette er et plot af: " << aName << endl;
	int space = 0;
	for (int i : aVector)
	{
		cout << i;
		space++;
		if (space > 7)
		{
			space = 0;
			cout << " ";
		}
	}
	cout << endl;
}