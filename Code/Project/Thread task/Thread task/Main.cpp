#include <iostream>
//#include <string>
#include <thread>

using namespace std;

void function_1() {
	cout << "Life is life" << endl;
	
}

int main() {
	std::thread t1(function_1);
	t1.detach();
	cout << " nana na-na-na " << endl;

	if (t1.joinable())
		t1.join();

	cout << "Dette er string" << endl;
	


	return 0;
}