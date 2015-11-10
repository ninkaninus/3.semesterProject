#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


//function declrations
void generateCRC(vector<bool>&, int& n);
//adds a CRC byte in the end of vector 

bool ChekCRC(vector<bool>&, int& n);
//checks CRC byte in the end of vector 

//hjælpefunktioner
void print(vector<bool>& aVector, string aName);
void fyldVector(vector<bool>& aVector);
void tilføjFejl(vector<bool>& aVector);


int main() {
		
		//opsætning
		vector<bool> hans;
		fyldVector(hans);
		print(hans, "hans original");	
		
		//afsender siden
		int n = 32;
		generateCRC(hans, n);
		print(hans, "hans med CRC");

		//fejl tilføjes
		//tilføjFejl(hans);
		//print(hans, "hans med fejl");
		


		//modtager siden
		cout << "dette udskriver crc status: " << ChekCRC(hans, n) << endl;
		print(hans, "hans original");

		return 0;
}

	//function definitions		
void generateCRC(vector<bool>& bVector, int& n)
{
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

	//opsætning
	vector<bool> CRC;
	for (bool i : bVector)
		CRC.push_back(i);
	for (int i = 0; i < n; i++)
		CRC.push_back(0);
		
	
	//Syndromet beregnes
	for (unsigned int i = 0; i < CRC.size() - n; i++)
	{
		if (CRC[i]) {
			// der er 1 - XOR
			for (int GEN = 0; GEN < n + 1; GEN++)
			{
				CRC[i + GEN] = CRC[i + GEN] ^ G[n - GEN];
			}
		}
	}
		
	//Syndrom tilføjes
	cout << "CRC er: ";
	for (unsigned int i = CRC.size() - n; i < CRC.size();i++) {
		bVector.push_back(CRC[i]);
		cout << CRC[i];
	}
}

bool ChekCRC(vector<bool>& bVector, int& n) {
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


//funktioner til debugging
void print(vector<bool>& aVector, string aName)
{
	cout << endl << "dette er  " << aName << endl;
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
	cout << endl << endl;
}

void fyldVector(vector<bool>& aVector)
{
	aVector.push_back(0);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(0);
	aVector.push_back(1);
	aVector.push_back(0);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(0);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(0);
	aVector.push_back(1);
	aVector.push_back(0);
	aVector.push_back(1);


}

void tilføjFejl(vector<bool>& aVector) {
	int index = 5;
	int index2 = 6;
	int index3 = 7;
	vector<bool> temp;

	for (unsigned int i = 0; i < aVector.size(); i++) {
		if (i == index) {
			temp.push_back(1);
		}
		else if (i == index2) {
			temp.push_back(0);
		}
		else if (i == index3) {
			temp.push_back(1);
		}
		else
			temp.push_back(aVector[i]);
	}
	
	aVector.clear();
	for (bool i : temp) {
		aVector.push_back(i);
	}
}
