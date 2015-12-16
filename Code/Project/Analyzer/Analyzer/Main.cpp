#include "Physical_Receive.h"
#include <thread>

int main()
{
	Physical_Receive Receiver;
	Receiver.init(8000, 25);

	Receiver.startRecording();
	Sleep(2000);

	std::thread analysis(&Physical_Receive::continuousAnalysis,&Receiver);
	analysis.detach();

	while (true)
	{
		Sleep(4000);

		if (Receiver.getBools().size() > 1)
		{
			for (int i = 0; i < Receiver.getBools().size(); i++)
			{
				std::cout << Receiver.getBools()[i] << " ";
			}
		}
	}

	return 0;
}