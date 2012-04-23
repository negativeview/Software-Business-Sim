#include "Platform.h"

Platform::Platform(string name) : RequirementProviderConsumer("platform", name.c_str()) {
	this->_name = name;
}

string Platform::getName() {
	return this->_name;
}

Platform::~Platform() {
}
