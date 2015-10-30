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

int main() {
		vector<int> hans;
	
		
		hans.push_back(0x10);
		hans.push_back(0x00);
		hans.push_back(0x00);
		hans.push_back(0x00);

		generateCRC(hans);	
		for (unsigned int y=0; y < hans.size(); y++) {
			cout << hans[y] << endl;
		}
		return 0;
	}

	//function definitions
void generateCRC(vector<int>& iVector)
{
	//opsætning
	iVector.push_back(0x00);
	int iByte = iVector[0];
	iByte = (iByte << 8);

	int Loop;
	for (unsigned int i = 1; i < iVector.size(); i++)
	{
		iByte = iByte | iVector[i];
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

	iByte = iByte >> 8;
	iVector.pop_back();
	iVector.push_back(iByte);
}
		
