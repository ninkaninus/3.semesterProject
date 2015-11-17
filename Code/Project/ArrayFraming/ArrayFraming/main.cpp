#include <iostream>
#include <string>
#include "DataLinkTransmit.h"
using namespace std;
int main()

{
	string str;
	cout << "Enter message" << endl;
	getline(cin, str);
	vector<int> aVector;
	int index;
	cout << "Enter index" << endl;
	std::cin >> index;
	int maxindex;
	cout << "Enter maxindex" << endl;
	std::cin >> maxindex;

	for(int i = 0; i < str.length() ;i++)	
		aVector.push_back(str[i]);
	DataLinkTransmit objekt;
	objekt.assembleFrame(aVector, index, maxindex);
	
}