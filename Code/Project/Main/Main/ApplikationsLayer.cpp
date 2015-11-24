#include "ApplikationsLayer.h"



ApplikationsLayer::ApplikationsLayer()
{
}


ApplikationsLayer::~ApplikationsLayer()
{
}

void ApplikationsLayer::dataToBoolean(string aString) // konverterer indkommen data til bool
{
	data.clear();
	for (int i = 0; i < aString.size(); i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			bitset<8> bits(aString[i]);
			data.push_back(bits[j]);
		}
	//	cout << endl;
	}

	//for (unsigned int i = 0; i < data.size(); i++)
	//	cout << data[i] << endl;
}				

void ApplikationsLayer::send(vector<bool>& iVector)	//sender input
{

}

vector<bool> ApplikationsLayer::returnData()
{
	return data;
}
