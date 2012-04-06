#include "Company.h"
#include <string.h>
#include <stdlib.h>

Company::Company(const char *name, int money) {
	this->_name = (char *)malloc(strlen(name) + 1);
	strcpy(this->_name, name);
	this->_money = money;
}

const char *Company::getName() {
	return this->_name;
}

Company::~Company() {
	free(this->_name);
	this->_name = NULL;
}
