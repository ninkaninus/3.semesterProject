#include <iostream>
#include <string>
#include "Frame.h"
using namespace std;
int main()

{
	while (true)
	{
	string str;
	cout << "Enter message" << endl;
	getline(cin, str);
	Frame test1(str);
	test1.printFrames();
	test1.printText();
	}
}