#include "TransportLayer.h"
#include <Constants.h>

TransportLayer::TransportLayer()
{

}

void TransportLayer::calculateIndex(unsigned int payloadSize)
{
	if (payloadSize <= BITS_IN_FRAME) {
		maxIndex = 0;
		return;
	}

	if (payloadSize % BITS_IN_FRAME == 0) {
		maxIndex = (payloadSize / BITS_IN_FRAME) - 1;
	}
	else {
		maxIndex = int(payloadSize / BITS_IN_FRAME);
	}
}

vector<bool> TransportLayer::extractPayload(unsigned int anIndex)
{
	vector<bool>::const_iterator first;
	vector<bool>::const_iterator last;

	if (anIndex < maxIndex) {
		first = input.begin() + (anIndex * BITS_IN_FRAME);
		last = input.begin() + ((anIndex * BITS_IN_FRAME) + BITS_IN_FRAME);
	}
	else {
		first = input.begin() + (anIndex * BITS_IN_FRAME);
		last = input.end();
	}
	vector<bool> pl(first, last);
	return pl;
}

void TransportLayer::setStatus(bool SR)
{}


void TransportLayer::send(vector<bool>& bVector)
{
	index = 0;

	input = bVector;

	calculateIndex(bVector.size());

	cout << "Max index: " << maxIndex << endl << endl;

	DTMF::Frame frame;

	for (int i = 0; i <= maxIndex; i++) {
		cout << "Payload: " << i << endl;
		frame.payload = extractPayload(i);
		frame.index = i;
		frame.maxIndex = returnMaxIndex();
		dataLinkT.transmitFrame(frame);
		cout << endl;
	}
}

int TransportLayer::returnMaxIndex() const
{
	return maxIndex;
}

TransportLayer::~TransportLayer()
{}

