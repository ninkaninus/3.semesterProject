#include "Frame.h"


Frame::Frame(void)
{
}


Frame::~Frame(void)
{
}

Frame::Frame(string enC)
{
	chat = enC;
	myFrame.push_back(32);					//Placeholder til preamble
	myFrame.push_back(126);					//Flag
	myFrame.push_back(1);					//Placeholder til Sekvensnummer
	for(int i = 0; i < chat.length();i++)	//Tekst
	myFrame.push_back(chat[i]);	
											//Trailer
	myFrame.push_back(126);					//Flag

}

void Frame::printText()
{
	cout << chat << endl;
}
	
void Frame::printFrames()
{
	for(unsigned int i = 0; i < myFrame.size(); i++)
		cout << myFrame[i] << endl;
}