#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//function declrations

//Afsender siden
void bitStuffing(vector<bool>& iVector);

//modtager siden
void antiBitStuffing(vector<bool>& iVector);

//hjælpefunktioner
void print(vector<bool>& aVector, string aName);
void fyldVector(vector<bool>& aVector);


int main() {
		//opsætning
		vector<bool> hans;
		fyldVector(hans);      // er nået til denne

		//afsender siden bitstuffing
		print(hans, "hans");
		bitStuffing(hans);
		print(hans, "hans med bitstuffing");
	

		//Modtagersiden siden bitstuffing
		antiBitStuffing(hans);
		print(hans, "hans original");

		return 0;
}


//function definitions	
void bitStuffing(vector<bool>& bVector)
{
	//opsætning af variable
	vector<bool> stuff;
	int loop=0;

	//Stuffing
	for(bool i : bVector)
	{
		stuff.push_back(i);
		if (i) {
			//1
			loop++;
			if (loop == 5) {
				//der er et flag
				cout << "flag" << endl;
				stuff.push_back(0);
				loop = 0;
			}
		}
		else {
			//0
			loop = 0;
		}
	}
	
	//smid stuff over i bVector
	bVector.clear();

	for (bool i : stuff)
		bVector.push_back(i);
}

void antiBitStuffing(vector<bool>& bVector)
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


//funktioner til debugging
void print(vector<bool>& aVector, string aName) 
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

void fyldVector(vector<bool>& aVector) 
{
	aVector.push_back(0);
	aVector.push_back(1);
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
	aVector.push_back(0);
	aVector.push_back(0);
	

}