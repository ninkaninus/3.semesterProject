#pragma once


class DataLinkTransmit
{
public:
	DataLinkTransmit();
	void generateCRC();
	void bitStuffing();
	void assembleFrame(vector<int>& payload,int index);
	~DataLinkTransmit();

private:
	int index;
	vector<int> payload;
};

