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
	if (this->_discoveryLevel > 3)
		this->_discoveryLevel = 3;
}

string Trait::getName() {
	return this->_name;
}

/**
 * This needs a lot of tweaking. For one, the discovery level needs to be stored
 * outside of the actual trait in order to promote reuse.
 *
 * The bigger challenge though is that this needs to be less predictable.
 *
 * I see more ranges here:
 *
 * 0) "unknown"
 * 1) "high, medium, or low"
 * 2-10) n-m where n and m are the right number +- rand() % (10 - x)
 *
 * A big challenge here then is that this text will have to be stored somewhere
 * so that it doesn't fluctuate every time it's queried.
 */
string Trait::getDiscoveryModifiedText() {
	stringstream tmp;
	string ret;

	switch (this->_discoveryLevel) {
		case 3:
			tmp << this->_amount;
			tmp >> ret;
			return ret;
			break;
		case 2:
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
		case 1:
			if (this->_amount < 33)
				return "low";
			if (this->_amount < 66)
				return "medium";
			return "high";
			break;
		case 0:
		default:
			return "Unknown";
	}
}

Trait::~Trait() {
	
}