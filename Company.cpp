#include "Company.h"
#include <string.h>
#include <stdlib.h>

Company::Company(const char *name, int money) {
	this->_name = (char *)malloc(strlen(name) + 1);
	strcpy(this->_name, name);
	this->_money = money;
	this->_employees = new list<Person *>();
}

void Company::addEmployee(Person *person) {
	this->_employees->push_back(person);
}

const char *Company::getName() {
	return this->_name;
}

list <Person *> *Company::getEmployees() {
	return this->_employees;
}

void Company::payWages(int wages) {
	this->_money -= wages;
}

int Company::getMoney() {
	return this->_money;
}

Company::~Company() {
	free(this->_name);
	this->_name = NULL;
	delete this->_employees;
	this->_employees = NULL;
}
