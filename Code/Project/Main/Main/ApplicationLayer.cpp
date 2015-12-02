#include "ApplicationLayer.h"



ApplicationLayer::ApplicationLayer()
{

}




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

void ApplicationLayer::send(string message)	//sender input
{
	objT.send(dataToBoolean(message));
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