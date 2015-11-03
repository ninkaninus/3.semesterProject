#include "DataLinkTransmit.h"



DataLinkTransmit::DataLinkTransmit()
{
	GENERATOR = 0x107 << 7;
}

void DataLinkTransmit::bitStuffing(vector<int>& iVector, vector<int>& stuffVector)
{
	//opsætning af variable
	
	int iByte = 0;
	int Loop = 0;

	int stuffByte = 0;
	int stuffLoop = 0;



	//Syndromet beregnes
	for (int i : iVector)
	{
		iByte = iByte | i;
		Loop = 0;
		while (Loop < 8)
		{
			bitset<16> s(iByte);
			if (!s[15])
			{
				cout << s << endl;
				if (s[14] && s[13] && s[12] && s[11] && s[10])
				{
					cout << "dette er et falg der tilføjes " << 0 << endl;
					//to do
				}
			}
			else 
			{
				stuffByte = stuffByte >> 1 | 1;
				stuffLoop++;
			}
				

			if (!(stuffLoop < 8))
			{

			}
			iByte = iByte << 1;
			Loop++;
		}
	}

	//Syndromet returneres
	cout << "Syndromet er: " << iByte << endl;
	iVector.pop_back();
}



DataLinkTransmit::~DataLinkTransmit()
{
}
