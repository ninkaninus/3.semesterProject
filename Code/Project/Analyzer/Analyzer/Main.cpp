#include "Physical_Receive.h"

int main()
{
	Physical_Receive Receiver;
	Receiver.init(8000, 25);

	Receiver.startRecording();
	Sleep(2000);

	Receiver.continuousAnalysis();

	return 0;
}