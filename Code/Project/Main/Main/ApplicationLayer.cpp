#include "ApplicationLayer.h"



ApplicationLayer::ApplicationLayer()
{

}

/*
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
*/

ApplicationLayer::~ApplicationLayer()
{
}

vector<bool> ApplicationLayer::dataToBoolean(string aString) // konverterer indkommen data til bool
{
	vector<bool> data;

	for (unsigned int i = 0; i < aString.size(); i++)
	{
		for (int j = 7; j >= 0 ; j--)
		{
			bitset<8> bits(aString.at(i));
			data.push_back(bits[j]);
		}
	}

	return data;
}

string ApplicationLayer::BooleanTodata(vector<bool>& bVector)
{

	//Sæt værdierne fra vectoren ind i en stringstream
	stringstream bool_value;
	for (unsigned int i = 0; i < bVector.size(); i++)
		bool_value << bVector[i];
	

	//Der oversættes til en string 
	string w = bool_value.str();

	//cout << w << endl;

	//Tag stringen og læg værdierne ind i et bitset. Lav de bits om til int og derefter til chars.

	string ind = w;
	stringstream sstream(ind);
	string ud;
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ullong());
		ud += c;
		//	ud += "endl";
		//	cout << ud;
	}

	//cout << ud << endl; //print værdien af boolvectoren ud som ASCII

	return ud;
}

void ApplicationLayer::newMessage()
{
	mutex.lock();
	
	if (!messageBuffer.empty())
	{
		std::vector<bool> temp = dataToBoolean(messageBuffer[0]);
		messageBuffer.pop_front();
		int length = temp.size();
		std::vector<bool>* boolPtr;
		boolPtr = new std::vector<bool>;

		for (int j = 31; j >= 0; j--)
		{
			bitset<32> bits(length);
			boolPtr->push_back(bits[j]);
		}

		for (int i = 0; i < BITS_IN_FRAME - 32; i++)
		{
			boolPtr->push_back(temp[i]);
		}

		temp.erase(temp.begin(), temp.begin() + BITS_IN_FRAME);

		currentBuffer.push_back(boolPtr);

		while (temp.size() > BITS_IN_FRAME)
		{
			boolPtr = new std::vector<bool>;
			for (int i = 0; i < BITS_IN_FRAME; i++)
			{
				boolPtr->push_back(temp[i]);
			}

			currentBuffer.push_back(boolPtr);

			temp.erase(temp.begin(), temp.begin() + BITS_IN_FRAME);

		}

		boolPtr = new std::vector<bool>;
		for (int i = 0; i < temp.size(); i++)
		{
			boolPtr->push_back(temp[i]);
		}

		currentBuffer.push_back(boolPtr);
	}

	mutex.unlock();
}

void ApplicationLayer::handleTransmit()
{
	if (objT.checkPacketBuffer())
	{
		objT.setPacket(currentBuffer[0]);
		currentBuffer.pop_front();
	}
	if (currentBuffer.empty())
	{
		newMessage();
	}
}

void ApplicationLayer::handleReceive()
{
	std::vector<bool>* tempChunk = objT.getPacketFromQueue();

	if(tempChunk != nullptr)
}

void ApplicationLayer::loop()
{
	while (true);
	{
		handleTransmit();
		handleReceive();
	}
}

void ApplicationLayer::send(string message)	//sender input
{
	mutex.lock();
	messageBuffer.push_back(message);
	mutex.unlock();
}



void ApplicationLayer::print(vector<bool>& aVector, string aName)
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