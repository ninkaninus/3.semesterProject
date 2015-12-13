#include "DataLinkReceive.h"
#include <iostream>


DataLinkReceive::DataLinkReceive() {
	init(8000, 25);
}

void DataLinkReceive::makeMessage()
{
	// Opsætning 
	DTMF::Frame newFrame;
	vector<bool> frame = objR.extractBoolVector();

	//print(frame, "frame før");
	//print(data, "data før");

	if (fail > 1)
		objR.setSyncMode(true);

	// Tilføje bools til data vectoren 
	for (bool i : frame) {
		data.push_back(i);
	}
	frame.clear();


	// Find næste frame af data
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

			// tilføj data uden frame 
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
				//std::cout << "valid frame " << std::endl;
				fail = 0;

				// Bestem frame typen
				newFrame.type = getInfo(frame, 0, 4);
				switch (newFrame.type) {
				case 0:
					// Dette er en frame
					// Extract information fra frame
					newFrame.payload = vector<bool>(frame.begin() + 12, frame.end());
					newFrame.index = getInfo(frame, 8, 12);
					newFrame.adress = getInfo(frame, 4, 8);
					break;
				case 1:
					// Dette er en ACK
					// Extract information fra frame
					newFrame.index = getInfo(frame, 8, 12);
					newFrame.adress = getInfo(frame, 4, 8);
					break;
				}
				
				// gem frame information i toTrans
				toTrans.push_back(newFrame);

				// til debugging plot tekst
				std::cout << BooleanTodata(newFrame.payload) << std::endl;
				
				cout << "Type:    " << newFrame.type << endl;
				cout << "Adresse: " << newFrame.adress << endl;
				cout << "Index:   " << newFrame.index << endl;

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

DTMF::Frame DataLinkReceive::getFrame()
{
	DTMF::Frame temp = toTrans[0];
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


unsigned int DataLinkReceive::getInfo(vector<bool>& bVector, int start, int stop)
{
	vector<bool> temp(bVector.begin() + start, bVector.begin() + stop);
	//print(temp, "Dette er temp");

	unsigned int num = 0;
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		num |= temp[i] << temp.size() - i - 1;
	}
	//cout << num << endl;
	return num;
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
	//opsætning
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
	for (unsigned int i = 0; i < stuff.size();i++)
		bVector.push_back(stuff[i]);
}

bool DataLinkReceive::ChekCRC(vector<bool>& bVector) {

	unsigned int n = DTMF::CRCnr;
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


	//Opsætning
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
	return ChekCRC(bVector);
}

string DataLinkReceive::BooleanTodata(vector<bool>& bVector)
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