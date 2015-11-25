#include "Physical_Receive.h"
#include <Windows.h>

int main()
{
	Physical_Receive Receiver;
	Receiver.init(8000, 100);

	std::cout << "Recording" << std::endl;

		Receiver.startRecording();
		Sleep(10000);
		Receiver.stopRecording();

	std::cout << "Stopped Recording" << std::endl;
	
	//Receiver.analyzeBuffer();

	//Receiver.printChars();

	Receiver.printMagnitude('1');

	/*
	std::cout << "Size of active buffer: " << myAnalyzer.getActiveBuffer().size() << std::endl;

	std::cout << "First detected char: " << myAnalyzer.findFirstDTMF() << std::endl;

	std::cout << "Size of active buffer: " << myAnalyzer.getActiveBuffer().size() << std::endl;

	
	for (int iterator = 2; myAnalyzer.getActiveBuffer().size() > myAnalyzer.getSampleWindow() * 2; iterator++)
	{
		char detectedChar = myAnalyzer.findDTMF();
		std::cout << iterator << ". detected char: " << detectedChar << std::endl;
		if (detectedChar != '?')
			myAnalyzer.erasePreviousSamples();
		else
		{
			std::cout << "No more characters" << std::endl;
			break;
		}
	}
	*/

	return 0;
}