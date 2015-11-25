#include "Physical_Receive.h"


int main()
{
	Physical_Receive Receiver;
	Receiver.init(8000, 25);

	std::cout << "Recording" << std::endl;

		Receiver.startRecording();
		Sleep(10000);
		Receiver.stopRecording();

	std::cout << "Stopped Recording" << std::endl;

//	Receiver.analyzeBuffer();

	Receiver.printMagnitude('A');

	Receiver.continuousAnalysis();

	return 0;
}