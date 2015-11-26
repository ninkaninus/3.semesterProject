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

void ApplikationsLayer::send(string message)	//sender input
{
	
	DataLinkTransmit objD;
	DTMF::Transmitter objTransmit;
	
	dataToBoolean(message);
	objT.newInput(returnData());

	objT.getPayload(0);
	objD.assembleFrame(objT.returnPayload(), 0, objT.returnMaxIndex());
	objTransmit.transmit(objD.returnPayload());

	objT.getPayload(1);
	objD.assembleFrame(objT.returnPayload(), 1, objT.returnMaxIndex());
	objTransmit.transmit(objD.returnPayload());
}

vector<bool> ApplikationsLayer::returnData()
{
	return data;
}
