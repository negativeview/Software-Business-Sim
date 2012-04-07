#include "Trait.h"

Trait::Trait(string name) {
	this->_name = name;
}

int Trait::influenceOnSalaryRequirements() {
	return 0;
}

Trait::~Trait() {
	
}