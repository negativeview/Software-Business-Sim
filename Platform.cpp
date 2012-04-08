#include "Platform.h"

Platform::Platform(string name) {
	this->_name = name;
}

string Platform::getName() {
	return this->_name;
}

Platform::~Platform() {
}
