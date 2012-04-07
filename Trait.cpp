#include "Trait.h"

#include <sstream>
using std::stringstream;

Trait::Trait(string name, int amount) {
	this->_amount = amount;
	this->_name = name;
	this->_discoveryLevel = 0;
}

int Trait::influenceOnSalaryRequirements() {
	return 0;
}

void Trait::discoverMore() {
	this->_discoveryLevel++;
	if (this->_discoveryLevel > 2)
		this->_discoveryLevel = 2;
}

string Trait::getName() {
	return this->_name;
}

string Trait::getDiscoveryModifiedText() {
	stringstream tmp;
	string ret;

	switch (this->_discoveryLevel) {
		case 2:
			tmp << this->_amount;
			tmp >> ret;
			return ret;
			break;
		case 1:
			if (this->_amount < 10)
				return "< 10";
			if (this->_amount < 20)
				return "10s";
			if (this->_amount < 30);
				return "20s";
			if (this->_amount < 40)
				return "30s";
			if (this->_amount < 50)
				return "40s";
			if (this->_amount < 60)
				return "50s";
			if (this->_amount < 70)
				return "60s";
			if (this->_amount < 80)
				return "70s";
			if (this->_amount < 90)
				return "80s";
			return "90s";
			break;
		case 0:
		default:
			if (this->_amount < 33)
				return "low";
			if (this->_amount < 66)
				return "medium";
			return "high";
	}
}

Trait::~Trait() {
	
}