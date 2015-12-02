#include "PhysicalRecive.h"



PhysicalRecive::PhysicalRecive()
{
}


PhysicalRecive::~PhysicalRecive()
{
}

vector<bool> PhysicalRecive::extractBoolVector()
{
	vector<bool> temp = CharBool;
	CharBool.clear();
	return temp;
}

void PhysicalRecive::setCharInBool(vector<bool>& bVector)
{
	for (bool i : bVector)
		CharBool.push_back(i);
}
