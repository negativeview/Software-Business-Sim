#include "AmbitionTrait.h"

#include <stdlib.h>
#include <stdio.h>

AmbitionTrait::AmbitionTrait(int amount) : Trait("Ambition") {
	this->_amount = amount;
}

int AmbitionTrait::influenceOnSalaryRequirements() {
	return (this->_amount / 10.0) * ((rand() % 10) + 1) * 1000;
}