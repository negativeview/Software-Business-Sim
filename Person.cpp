#include "Person.h"
#include "Company.h"
#include <string.h>
#include <stdlib.h>

Person::Person(const char *firstName, const char *lastName, int money) {
	this->_firstName = (char *)malloc(strlen(firstName) + 1);
	this->_lastName = (char *)malloc(strlen(lastName) + 1);
	strcpy(this->_firstName, firstName);
	strcpy(this->_lastName, lastName);
	this->_money = money;
	this->_company = NULL;
}

Company *Person::getCompany() {
	return this->_company;
}

void Person::hire(Company *company) {
	this->_company = company;
}

const char *Person::getFirstName() {
	return this->_firstName;
}

const char *Person::getLastName() {
	return this->_lastName;
}

Person::~Person() {
	free(this->_firstName);
	this->_firstName = NULL;
	free(this->_lastName);
	this->_lastName = NULL;
}
