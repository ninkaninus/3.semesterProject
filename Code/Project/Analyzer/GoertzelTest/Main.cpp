#include "Analyzer.h"
#include <Windows.h>

int main()
{
	
	Analyzer myAnalyzer;
	myAnalyzer.init(8000,100); // Samplerate , Bredde af samplewindow i millisekunder

	std::cout << "Recording" << std::endl;

		myAnalyzer.startRecording();
		Sleep(5000);
		myAnalyzer.stopRecording();

	std::cout << "Stopped Recording" << std::endl;
	

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

	return 0;
}