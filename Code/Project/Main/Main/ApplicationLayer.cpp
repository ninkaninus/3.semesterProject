#include "ApplicationLayer.h"



ApplicationLayer::ApplicationLayer()
{
	std::thread appLoop(&ApplicationLayer::loop, this);
	appLoop.detach();
}

ApplicationLayer::~ApplicationLayer()
{
}

vector<bool> ApplicationLayer::dataToBoolean(string aString) // konverterer indkommen data til bool
{
	vector<bool> data;

	for (int i = 0; i < aString.size(); i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			bitset<8> bits(aString.at(i));
			data.push_back(bits[j]);
		}
	}

	return data;
}

string ApplicationLayer::booleanTodata(vector<bool>& bVector)
{

	//S�t v�rdierne fra vectoren ind i en stringstream
	stringstream bool_value;
	for (unsigned int i = 0; i < bVector.size(); i++)
		bool_value << bVector[i];


	//Der overs�ttes til en string 
	string w = bool_value.str();

	//cout << w << endl;

	//Tag stringen og l�g v�rdierne ind i et bitset. Lav de bits om til int og derefter til chars.

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

	//cout << ud << endl; //print v�rdien af boolvectoren ud som ASCII

	return ud;
}

void ApplicationLayer::newMessage()
{
	mutex.lock();

	if (!messageOutBuffer.empty())
	{
		std::vector<bool> temp = dataToBoolean(messageOutBuffer[0]);
		messageOutBuffer.pop_front();
		int length = temp.size();
		std::vector<bool>* boolPtr;
		boolPtr = new std::vector<bool>;

		// L�ngden af beskeden i bools, smides ind i de 32 f�rste bits i en ny besked..

		for (int j = 31; j >= 0; j--)
		{
			bitset<32> bits(length);
			boolPtr->push_back(bits[j]);
		}

		// Pakken fyldes op med data fra beskeden indtil st�rrelsen af den n�r BITS_IN_FRAME, eller til hele beskeden er gemt i en pakke.

		int charCount;

		if (temp.size() < BITS_IN_FRAME - 32)
			charCount = temp.size();
		else
			charCount = BITS_IN_FRAME - 32;

		for (unsigned int i = 0; i < charCount; i++)
		{
			boolPtr->push_back(temp[i]);
		}

		temp.erase(temp.begin(), temp.begin() + charCount);

		currentBuffer.push_back(boolPtr);

		// Beskeden deles ind i pakker af st�rrelsen BITS_IN_FRAME, indtil der ikke kan laves flere af den st�rrelse

		while (temp.size() > BITS_IN_FRAME)
		{
			boolPtr = new std::vector<bool>;
			for (unsigned int i = 0; i < BITS_IN_FRAME; i++)
			{
				boolPtr->push_back(temp[i]);
			}

			currentBuffer.push_back(boolPtr);

			temp.erase(temp.begin(), temp.begin() + BITS_IN_FRAME);
		}

		// Hvis der er noget resterende her, smides det ind i en mindre pakke

		if (temp.size() != 0)
		{
			boolPtr = new std::vector<bool>;
			for (unsigned int i = 0; i < temp.size(); i++)
			{
				boolPtr->push_back(temp[i]);
			}

			currentBuffer.push_back(boolPtr);
		}
	}

	mutex.unlock();
}

void ApplicationLayer::handleTransmit()
{
	if (objT.checkPacketBuffer())
	{
		if (!currentBuffer.empty())
		{
			objT.setPacket(currentBuffer[0]);
			currentBuffer.pop_front();
		}
	}
	if (currentBuffer.empty())
	{
		newMessage();
	}
}

void ApplicationLayer::handleReceive()
{
	std::vector<bool>* tempChunk = objT.getPacketFromQueue();

	while (tempChunk != nullptr)
	{
		if (messageComplete)
		{
			// find ny l�ngde + chars
			messageComplete = false;
			lengthOfMessage = 0;

			for (unsigned int i = 0; i < 32; i++)
			{
				lengthOfMessage |= tempChunk->at(i) << 32 - i - 1;
			}

			tempChunk->erase(tempChunk->begin(), tempChunk->begin() + 32);

			messageIn += booleanTodata(*tempChunk);

			if (messageIn.length() - 1 == lengthOfMessage / 8)
			{
				messageComplete = true;
				lengthOfMessage = 0;

				mutex.lock();
				messageInBuffer.push_back(messageIn);
				mutex.unlock();
				
				cout << "Jonas siger: " << messageIn << endl;
				messageIn = "";
			}
			delete tempChunk;
		}
		else
		{
			messageIn += booleanTodata(*tempChunk);
			if (messageIn.length() == lengthOfMessage / 8)
			{
				messageComplete = true;
				lengthOfMessage = 0;

				mutex.lock();
				messageInBuffer.push_back(messageIn);
				mutex.unlock();


				cout << "Incoming!! " << messageIn << endl;
				messageIn = "";

			}
				delete tempChunk;
		}

		tempChunk = objT.getPacketFromQueue();
	}
	delete tempChunk;
}

void ApplicationLayer::loop()
{
	while (true)
	{
		Sleep(500);
		handleTransmit();
		handleReceive();
	}
}

void ApplicationLayer::send(string message)	//sender input
{
	mutex.lock();
	messageOutBuffer.push_back(message);
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
