#include "Language.h"

Language::Language(string name) {
	this->_name = name;
}

string Language::getName() {
	return this->_name;
}

Language::~Language() {
	
}