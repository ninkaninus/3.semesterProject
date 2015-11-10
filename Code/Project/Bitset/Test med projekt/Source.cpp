#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//function declrations

//Afsender siden
void stuffinator(vector<int>& stuffVector, bool bit);
void copyStuffToPayload(vector<int>& iVector, vector<int>& stuffVector);
void bitStuffing(vector<int>& iVector);
//bitstuffing og 0 padding (note: der paddes ikke efter standarden)


//modtager siden
void antiBitStuffing(vector<int>& iVector);


//hjælpefunktioner
void print(vector<int>& aVector, string aName);
void fyldVector(vector<int>& aVector);


int main() {
		//opsætning
		vector<int> hans;
		fyldVector(hans);

		//afsender siden bitstuffing
		print(hans, "hans");
		bitStuffing(hans);
		print(hans, "hans med bitstuffing vertion 2.0");
	

		//Modtagersiden siden bitstuffing
		antiBitStuffing(hans);
		print(hans, "hans original");

		return 0;
}


//function definitions		
void bitStuffing(vector<int>& iVector)
{
	//opsætning af variable
	vector<int> stuffVector;
	stuffVector.push_back(0x01);
	iVector.push_back(0x00);
	
	int iByte = 0;
	int Loop = 0;
	int igen = 5;

	//Stuffing
	for (unsigned int i = 0; i < iVector.size() - 1; i++)
	{
		iByte = iByte | iVector[i];
		Loop = 0;
		while (Loop < 8)
		{
			bitset<16> s(iByte);
			stuffinator(stuffVector, s[7]);
			if ((s[7] && s[8] && s[9] && s[10] && s[11] && s[12] && (!(s[13]))))
			{	
				stuffinator(stuffVector, 1);
			}
			iByte = iByte << 1;
			Loop++;
		}
	}

	//Afslut med at lægge alt tilbage i den gamle vektor
	copyStuffToPayload(iVector, stuffVector);
}

void stuffinator(vector<int>& stuffVector, bool bit)
{
	//opsætning af værider
	int stuffByte = stuffVector[stuffVector.size() - 1];
	bitset<8> b(stuffByte);
	
	//chekke om sidste byte er fyldt
	if (b[7])
	{
		stuffByte = (stuffByte << 1) + bit;
		stuffVector.pop_back();
		stuffVector.push_back(stuffByte);

		stuffVector.push_back(0x01);
	}
	else {
		stuffByte = (stuffByte << 1) + bit;
		stuffVector.pop_back();
		stuffVector.push_back(stuffByte);
	}



	//display 
	/*for (int i : stuffVector)	{
		bitset<8> b(i);
		cout << b << " ";
	}
	cout << endl;*/
}

void copyStuffToPayload(vector<int>& iVector, vector<int>& stuffVector) 
{
	iVector.clear();
	for (int i : stuffVector) {
		iVector.push_back(i);
	}
}


void antiBitStuffing(vector<int>& iVector)
{
	//opsætning
	vector<int> stuffVector;
	stuffVector.push_back(0x01);
	iVector.push_back(0x00);

	unsigned int iByte = 0;
	int Loop = 0;
	cout << "1." << endl;
	//antistuffing
	for (unsigned int i = 0; i < iVector.size() - 1; i++)
	{
		iByte = iByte | iVector[i];
		Loop = 0;
		while (Loop < 8)
		{
			bitset<16> s(iByte);
			//cout << s << endl;
			if (!(s[7] && s[8] && s[9] && s[10] && s[11] && s[12] && (!s[13]))) {
				stuffinator(stuffVector, s[7]);
			}

			iByte = iByte << 1;
			Loop++;
		}
	}

	cout << "2." << iByte << endl;
	//behandling af den sidst byte (lappeløsning)
	int n = 0;
	bitset<16> u(iByte);
	cout << u << endl;
	iByte = iByte & 0b1111111111111111;
	bitset<16> s(iByte);
	cout << s << endl;
	while (iByte < 0b1000000000000000) {
		iByte *= 2;
		bitset<16> s(iByte);
		cout << "nu:    " << s << endl;
		n++;
	}
	cout << "3." << endl;

	iByte = iByte >> 7;
	iByte = iByte & 0b11111111;
	iByte = iByte | (iVector[iVector.size() - 3] << 8);

	n = 8 - n;

	bitset<16> ta(iByte);
	//cout << "efter: " << ta << endl;
	//cout << n <<  endl;

	while (n > 0)
	{
		bitset<16> s(iByte);

		if (!(s[7] && s[8] && s[9] && s[10] && s[11] && s[12] && (!s[13]))) {
			stuffinator(stuffVector, s[7]);
		}

		iByte = iByte << 1;
		n--;
	}

	//smid resultatet tilbage i iVector
	stuffVector.pop_back();
	copyStuffToPayload(iVector, stuffVector);

}

//funktioner til debugging
void print(vector<int>& aVector, string aName) 
{
	cout << endl << "dette er " << aName << endl;
	for (int i : aVector)
	{
		bitset<8> b(i);
		cout << b << " ";
	}
	cout << endl;
}

void fyldVector(vector<int>& aVector) 
{
	aVector.push_back(0x77);
	aVector.push_back(0x00);
	aVector.push_back(0xF7);
	aVector.push_back(0x8B);
	aVector.push_back(0xA8);
	aVector.push_back(0x01);
	aVector.push_back(0xFC);
	aVector.push_back(0x80);
	aVector.push_back(0x88);
	aVector.push_back(0x01);

}