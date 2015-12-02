#include "DataLinkRecive.h"
#include <iostream>


DataLinkRecive::DataLinkRecive()
{
	//dette er til test
	vector<bool> sim = { 0, 1, 1, 1, 1, 1, 1, 0,	0, 0, 0, 0, 0, 0, 0, 0,		 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 1, 0, 0, 1, 0,		1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 };
	objR.setCharInBool(sim);
}

void DataLinkRecive::makeFrame()
{
	// Opsætning 
	Frame newFrame;
	vector<bool> frame = objR.extractBoolVector();
	print(frame, "Frame efter");
	print(data, "data efter");

	// Tilføje bools til data vectoren 
	for (bool i : frame)
		data.push_back(i);
	frame.clear();

	
	// Find næste frame af data
	int aFlag = 0;
	int length = 0;

	for (unsigned int i = 7; i < data.size(); i++)
	{
		length++;

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
	vector<bool> temp;
	for (unsigned int i = 0; i < data.size(); i++) {
		if (i > length + 6)
			temp.push_back(data[i]);
	}

	data.clear();
	for (bool i : temp)
		data.push_back(i);

	
	// antibitstuffing 
	antiBitStuffing(frame);

	
	// CRC og validering
	int n = 32;
	if (validFrame(frame))
	{
		cout << "valid frame " << endl;
		// extract payload
		newFrame.payload = 	getPayload(frame);

		// extract index
		newFrame.index = getIndex(frame);

		// extract maxIndex
		newFrame.maxIndex = getMaxIndex(frame);

		cout << BooleanTodata(newFrame.payload) << endl;
	}
	else
	{
		cout << "deffekt frame" << endl;
		
	}

	// Består den testen returneres payload ellers returneres en tom vektor
	toTrans.push_back(newFrame);
	print(toTrans[toTrans.size() - 1].payload, "Frame efter");
	print(data, "data efter");
	
	
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
// to do
unsigned int DataLinkRecive::getIndex(vector<bool>& bVector)
{
	return 0;
}

// to do
unsigned int DataLinkRecive::getMaxIndex(vector<bool>& bVector)
{

	return 0;
}

vector<bool> DataLinkRecive::getPayload(vector<bool>& bVector)
{
	vector<bool> temp;
	for (unsigned int i = 0; i < bVector.size(); i++) {
		if (i >= 16) {
			temp.push_back(bVector[i]);
		}
	}

	return temp;
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

void DataLinkRecive::antiBitStuffing(vector<bool>& bVector)
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
				cout << "flag" << endl;
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
	for (bool i : stuff)
		bVector.push_back(i);
}

bool DataLinkRecive::ChekCRC(vector<bool>& bVector, int& n) {
	//Valg af generatorpolynomium
	double GENERATOR = 0;

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
		cout << "Fejl CRC ugyldigt skal vaere 8, 10, 16 eller 32 " << endl << n << " blev brugt, der erstattes med " << 8 << endl;
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

bool DataLinkRecive::validFrame(vector<bool>& bVector)
{
	int n = 32;
	return ChekCRC(bVector,n);
}

string DataLinkRecive::BooleanTodata(vector<bool>& bVector)
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