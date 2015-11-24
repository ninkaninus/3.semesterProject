#include "TransportLayer.h"

TransportLayer::TransportLayer()
{}

void TransportLayer::newInput(vector<bool>& anInput)
{
	index = 0;
	CHARS_IN_FRAME = 3*8;
	for (int i = 0; i < anInput.size(); i++)
		input.push_back(anInput[i]);

	if (input.size() % CHARS_IN_FRAME == 0)
		maxIndex = anInput.size() / CHARS_IN_FRAME - 1;
	else
		maxIndex = anInput.size() / CHARS_IN_FRAME;

	cout << "maxIndex er :" << maxIndex << endl;
}

void TransportLayer::getPayload(int anIndex)
{
	payload.clear();
	if (input.size() % CHARS_IN_FRAME != 0 && input.size() - (anIndex*CHARS_IN_FRAME) < CHARS_IN_FRAME && anIndex <= maxIndex) //maxindex skal findes matematisk
	{
		for (int i = anIndex*CHARS_IN_FRAME; i < anIndex*CHARS_IN_FRAME + (input.size() % CHARS_IN_FRAME); i++)
		{
			payload.push_back(input[i]);
		}
	}
	else
	{
		for (int i = anIndex*CHARS_IN_FRAME; i < (anIndex*CHARS_IN_FRAME + CHARS_IN_FRAME); i++)			//Tekst
		{
			payload.push_back(input[i]);
		}
	
	}
	
//	for (unsigned int i = 0; i < payload.size(); i++)
	//	cout << payload[i] << endl;
}

void TransportLayer::nextIndex()
{
	index++;
}

void TransportLayer::setStatus(bool SR)
{}

void TransportLayer::sendPayload()
{}

TransportLayer::~TransportLayer()
{}

vector<bool> TransportLayer::returnPayload()
{
	return payload;
}

int TransportLayer::returnMaxIndex()
{
	return maxIndex;
}