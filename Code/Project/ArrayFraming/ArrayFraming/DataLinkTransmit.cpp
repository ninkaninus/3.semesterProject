#include "DataLinkTransmit.h"


DataLinkTransmit::DataLinkTransmit(void)
{
}


DataLinkTransmit::~DataLinkTransmit(void)
{
}

DataLinkTransmit::DataLinkTransmit(string enC)
{
	index = 0;
	chat = enC;
	for(int i = 0; i < chat.length()/CHARS_IN_DataLinkTransmit;i++)
		{
		myFrame.push_back(32);										//Placeholder til preamble
		myFrame.push_back(126);										//Flag
		myFrame.push_back(1);										//Placeholder til Sekvensnummer
		for(int i = index; i < (index+CHARS_IN_DataLinkTransmit);i++)			//Tekst
			myFrame.push_back(chat[i]);
		myFrame.push_back(126);										//Flag
		index=+CHARS_IN_DataLinkTransmit;
		printDataLinkTransmits();												//placeholder for at sende DataLinkTransmit videre
		myFrame.clear();											//tøm DataLinkTransmit, klar til næste
		}


	if(chat.length()%CHARS_IN_DataLinkTransmit!=0)
		{
		myFrame.push_back(32);							
		myFrame.push_back(126);							
		myFrame.push_back(1);	
		for(int i = index; i < (index+chat.length()%CHARS_IN_DataLinkTransmit);i++)
			{
			myFrame.push_back(chat[i]);
			}
		myFrame.push_back(126);							
		printDataLinkTransmits();									
		myFrame.clear();
		}
}

void DataLinkTransmit::printText()
{
	cout << chat << endl;
}
	
void DataLinkTransmit::printDataLinkTransmits()
{
	for(unsigned int i = 0; i < myFrame.size(); i++)
		cout << myFrame[i] << endl;
}