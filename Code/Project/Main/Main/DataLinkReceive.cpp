#include "DataLinkReceive.h"
#include <iostream>


DataLinkReceive::DataLinkReceive()
{

}

void DataLinkReceive::makeMessage()
{
	// Ops�tning 
	Frame newFrame;
	vector<bool> frame = objR.extractBoolVector();

	//print(frame, "frame f�r");
	//print(data, "data f�r");

	if (fail > 1)
		objR.setSyncMode(true);

	// Tilf�je bools til data vectoren 
	for (bool i : frame) {
		data.push_back(i);
	}
	frame.clear();


	// Find n�ste frame af data
	int aFlag = 0;
	int length = 7;
	if (data.size() > 10)
	{
		for (unsigned int i = 8; i < data.size() + 1; i++)
		{
			length++;

			// Led efter flag
			if (!data[i - 1] && data[i - 2] && data[i - 3] && data[i - 4] && data[i - 5] && data[i - 6] && data[i - 7] && !data[i - 8]) {
				//en frame er begyndt
				aFlag++;
			}

			// tilf�j data uden frame 
			if (aFlag == 1){
				if (data.size() > i) {
					frame.push_back(data[i]);
				}
			}

			//stop hvis der et nyt flag
			if (aFlag > 1) {
				break;
			}
		}
			

		if(aFlag == 2){
			for (int i = 0; i < 8; i++) {
				frame.pop_back();
			}

			// Fjern denne frame fra data 
			data.erase(data.begin(), data.begin()+length - 8);
			antiBitStuffing(frame);			


			// CRC og validering
			if (validFrame(frame))
			{
				std::cout << "valid frame " << std::endl;
				fail = 0;
				// extract payload
				newFrame.payload = getPayload(frame);

				// extract index
				newFrame.index = getIndex(frame);

				// extract maxIndex
				newFrame.maxIndex = getMaxIndex(frame);

				toTrans.push_back(newFrame);
				std::cout << BooleanTodata(newFrame.payload) << std::endl;
			}
			else
			{
				fail++;
				std::cout << "defekt frame" << std::endl;
				std::cout << "Number of fails: " << fail << std::endl;
			}
		}
	}
}

Frame DataLinkReceive::getFrame()
{
	Frame temp = toTrans[0];
	toTrans.pop_front();
	return temp;
}

unsigned int DataLinkReceive::numberOfFrames()
{
	return toTrans.size();
}

void DataLinkReceive::init(int aSampleRate, int aProcessingTime)
{
	objR.init(aSampleRate, aProcessingTime);
	objR.startRecording();
	Sleep(2000);

	startAnalysis();

	fail = 0;

}

void DataLinkReceive::startAnalysis()
{
	std::thread analysis(&PhysicalReceive::continuousAnalysis, &objR);
	analysis.detach();
}

void DataLinkReceive::stopAnalysis()
{
	objR.stopAnalysis();
}


DataLinkReceive::~DataLinkReceive()
{
}
// to do
unsigned int DataLinkReceive::getIndex(vector<bool>& bVector)
{
	return 0;
}

// to do
unsigned int DataLinkReceive::getMaxIndex(vector<bool>& bVector)
{

	return 0;
}

vector<bool> DataLinkReceive::getPayload(vector<bool>& bVector)
{
	vector<bool> temp;
	for (unsigned int i = 0; i < bVector.size(); i++) {
		if (i >= 16) {
			temp.push_back(bVector[i]);
		}
	}

	return temp;
}

void DataLinkReceive::print(vector<bool>& aVector, string aName)
{
	std::cout << std::endl << "dette er et plot af: " << aName << std::endl;
	int space = 0;
	for (int i : aVector)
	{
		std::cout << i;
		space++;
		if (space > 7)
		{
			space = 0;
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

void DataLinkReceive::antiBitStuffing(vector<bool>& bVector)
{
	//ops�tning
	vector<int> stuff;
	int loop = 0;

	//antistuffing
	for (unsigned int i = 0; i < bVector.size(); i++)
	{
		stuff.push_back(bVector[i]);
		if (bVector[i]) {
			//1
			loop++;
			if (loop == 5) {
				//der er et flag
				//cout << "flag" << endl;
				i++;
				loop = 0;
			}
		}
		else {
			//0
			loop = 0;
		}
	}

	//smid resultatet tilbage i bVector
	bVector.clear();
	for (int i = 0; i < stuff.size();i++)
		bVector.push_back(stuff[i]);
}

bool DataLinkReceive::ChekCRC(vector<bool>& bVector, int& n) {
	//Valg af generatorpolynomium
	double GENERATOR = 0;

	if (bVector.size() < n) {
		return false;
	}

	switch (n)
	{
	case 8:
		GENERATOR = 0b100000111;
		break;
	case 10:
		GENERATOR = 0b11000110101;
		break;
	case 16:
		GENERATOR = 0b10001000000100001;
		break;
	case 32:
		GENERATOR = 0b100000100110000010001110110110111;
		break;
	default:
		std::cout << "Fejl CRC ugyldigt skal vaere 8, 10, 16 eller 32 " << std::endl << n << " blev brugt, der erstattes med " << 8 << std::endl;
		GENERATOR = 0b100000111;
		n = 8;
	}

	bitset<33> G(GENERATOR);


	//Ops�tning
	vector<bool> CRC;
	for (bool i : bVector)
		CRC.push_back(i);


	//Syndromet beregnes
	for (unsigned int i = 0; i < CRC.size() - n; i++)
	{
		if (CRC[i]) {
			// der er 1 - XOR

			for (int GEN = 0; GEN < n + 1; GEN++)
			{
				CRC[i + GEN] = CRC[i + GEN] ^ G[n - GEN];
			}
			//print(CRC, "test");
		}
	}


	//Syndrom fjernes
	for (unsigned int i = CRC.size() - n; i < CRC.size();i++) {
		bVector.pop_back();
	}

	//returner 1 hvis syndromet er 0 (ingen fejl) ellers returner 0
	for (bool i : CRC)
	{
		if (i)
			return 0;
	}
	return 1;
}

bool DataLinkReceive::validFrame(vector<bool>& bVector)
{
	int n = 32;

	return ChekCRC(bVector, n);
}

string DataLinkReceive::BooleanTodata(vector<bool>& bVector)
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