#include "Person.h"
#include "Company.h"

Person::Person(string firstName, string lastName, int money) {
	this->_firstName = firstName;
	this->_lastName = lastName;
	this->_money = money;
	this->_company = NULL;
}

Company *Person::getCompany() {
	return this->_company;
}

void Person::hire(Company *company) {
	this->_company = company;
}

string Person::getFirstName() {
	return this->_firstName;
}

string Person::getLastName() {
	return this->_lastName;
}

Person::~Person() {
}
