#pragma once
class DataLinkRecive
{
public:
	DataLinkRecive();
	void newFrame(vector<int> dataFrame);
	bool checkCRC();
	bool validFrame();
	void antiBitStuffing();
	void extractIndex();
	void extractPayload();
	~DataLinkRecive();

protected:
	vector<int> dataFrame;
	vector<int> payload;
	int index;

};

