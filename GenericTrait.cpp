#include "GenericTrait.h"

GenericTrait::GenericTrait(string name) {
	this->_name = name;
	this->_count = 0;
	this->_sum = 0;
}

void GenericTrait::addNewValue(int value) {
	this->_count++;
	this->_sum += value;
}

float GenericTrait::getAverageSkill() {
	return ((float)this->_sum) / this->_count;
}

string GenericTrait::getName() {
	return this->_name;
}