#pragma once
class PhysicalTransmit
{
public:
	PhysicalTransmit();
	bool getStatus();
	bool frameEndDetect();
	~PhysicalTransmit();

protected:
	vector<int> recivedFrame;
	// eventuelt en opbevaring af sampling 
	int index;
};

