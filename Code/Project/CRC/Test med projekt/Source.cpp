#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

	void foo(int &value)
	{
		value = 6;
	}

	int main()
	{
		int value = 5;

		cout << "value = " << value << '\n';
		foo(value);
		cout << "value = " << value << '\n';
		return 0;
	}
	/*string chat;
	chat = "hejsa";
	vector<bool> iVec;
	for (int i = 0; i < chat.size(); i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			bitset<8> bits(chat[i]);
			cout << bits[j] << endl;
			iVec.push_back(bits[j]);
		}
		cout << endl;
	}

	for (unsigned int i = 0; i < iVec.size(); i++)
		cout << iVec[i] << endl;
}*/

/*
//definitions
const int GENERATOR = 0x107 << 7;

//function declrations
void bitStuffing(vector<int>&, vector<int>&);

void generateCRC(vector<int>&);
//adds a CRC byte in the end of vector 

void ChekCRC(vector<int>&);
//checks CRC byte in the end of vector 


int main() {
	cout << 1 << endl;
		vector<int> hans;
		vector<int> stuff;
		stuff.push_back(0x00);
		
		cout << 2 << endl;
		hans.push_back(0x1F);
		hans.push_back(0xFF);
		hans.push_back(0x87);
		hans.push_back(0x79);
		hans.push_back(0x10);
		hans.push_back(0xFF);
		hans.push_back(0x87);
		hans.push_back(0x79);
		hans.push_back(0xFA);
		hans.push_back(0x11);
		hans.push_back(0x00);

		cout << 3 << endl;
			//afsender del
	
		//bitStuffing(hans, stuff);

		for (unsigned int y=0; y < hans.size(); y++) {
			cout << hans[y] << endl;
		}
		cout << 4 << endl;
		hans.clear();

		for (unsigned int y = 0; y < hans.size(); y++) {
			cout << hans[y] << endl;
		}

		return 0;
}

	//function definitions		
void ChekCRC(vector<int>& iVector) {
	//opsætning af variable
	int iByte = 0;
	int Loop = 0;

	//Syndromet beregnes
	for (int i : iVector)
	{
		iByte = iByte | i;
		Loop = 0;
		while (Loop < 8)
		{
			bitset<16> s(iByte);
			if (s[15])
				iByte = iByte ^ GENERATOR;

			iByte = iByte << 1;
			Loop++;
		}
	}

	//Syndromet returneres
	cout << "Syndromet er: " << iByte << endl;
	iVector.pop_back();
	
}

void generateCRC(vector<int>& iVector)
{
	//opsætning
	iVector.push_back(0x00);
	int iByte = 0;
	int Loop = 0;
	
	//Syndromet beregnes
	for (int i : iVector)
	{
		iByte = iByte | i;
		Loop = 0;
		while (Loop < 8)
		{
			bitset<16> s(iByte);
			if (s[15])
				iByte = iByte ^ GENERATOR;

			iByte = iByte << 1;
			Loop++;
		}
	}

	//Syndrom tilføjes
	iByte = iByte >> 8;
	iVector.pop_back();
	iVector.push_back(iByte);
}

void bitStuffing(vector<int>& iVector, vector<int>& stuffVector)
{
	//opsætning af variable
	stuffVector.clear();
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
}*/