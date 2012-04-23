#include "NamedObject.h"

#include <string.h>
#include <stdlib.h>

NamedObject::NamedObject(const char *tag, const char *fullName) {
	this->_tag = (char *)malloc(strlen(tag) + 1);
	strcpy(this->_tag, tag);

	this->_fullName = (char *)malloc(strlen(fullName) + 1);
	strcpy(this->_fullName, fullName);
}

const char *NamedObject::getTag() {
	return this->_tag;
}

const char *NamedObject::getFullName() {
	return this->_fullName;
}

NamedObject::~NamedObject() {
	free(this->_tag);
	free(this->_fullName);
}