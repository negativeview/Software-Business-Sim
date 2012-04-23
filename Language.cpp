#include "Language.h"

Language::Language(string name) : RequirementProviderConsumer("language", name.c_str()) {
	this->_name = name;
}

string Language::getName() {
	return this->_name;
}

Language::~Language() {
	
}