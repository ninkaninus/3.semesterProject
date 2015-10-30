#pragma once
class ApplikationsLayer
{
public:
	ApplikationsLayer();				
	void interfaceUpdate();				//eventuel understyttelse af UserInterface
	void xToData(string input);			//konverter fra input til vektor af bytes
	void dataToX();						//konverter fra vektor af bytes til output
	void dataTypeEstract();				//hvilken datatype der skal sende
	void send(vector<int> iVector);		//sender input

	~ApplikationsLayer();

protected:
	bool sendStatus;					//Er beskeden nået frem og klar til at sende igen
	vector<int> data;					//Den konverterede datastreng som skal sendes
	string input;						//Hvad en bruger vil sende
	int dataType;						//Her bruger vi et nummer til at indikere hvilken datatype der er tale om
};

