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

void Company::doPayments(int time) {
	// Every two weeks, pay your people.
	int totalPayout = 0;
	if (time % 14 == 0) {
		for (list<Person *>::iterator it = this->_employees->begin(); it != this->_employees->end(); ++it) {
			int salary = (*it)->getCurrentSalary();
			this->payWages(salary);
			(*it)->addMoney(salary);
			totalPayout += salary;
		}
	}

	int overheadCost = this->getOverheadCost();
	this->payOverhead(overheadCost);
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

void Company::payOverhead(int overhead) {
	this->_money -= overhead;
}

int Company::getOverheadCost() {
	// No matter what, you cannot get away scot free.
	int overhead = 1;

	overhead += this->_employees->size() * 10;

	// Every 10 days something random happens.
	// The higher your everyday costs, the more
	// an occurence costs.
	if (rand() % 10 == 0)
		overhead *= (rand() % 100) / 50.0;

	return overhead;
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
