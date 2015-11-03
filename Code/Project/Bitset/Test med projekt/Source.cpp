#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//definitions
const int GENERATOR = 0x107 << 7;

//function declrations
void generateCRC(vector<int>&);
//adds a CRC byte in the end of vector 

void ChekCRC(vector<int>&);
//checks CRC byte in the end of vector 


int main() {
		vector<int> hans;
		
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


		//afsender del
		generateCRC(hans);	

		for (int y=0; y < hans.size(); y++) {
			cout << hans[y] << endl;
		}
		
		cout << "der tilføjes fejl på plas 2" << endl << endl;

		hans[2] = 0x88;
		hans[10] = 0x73;

		for (unsigned int y = 0; y < hans.size(); y++) {
			cout << hans[y] << endl;
		}
		cout << endl;

		//modtager
		ChekCRC(hans);
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