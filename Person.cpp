#include "Person.h"
#include "Company.h"

#include <stdlib.h>

Person::Person(string firstName, string lastName, int money) {
	this->_firstName = firstName;
	this->_lastName = lastName;
	this->_money = money;
	this->_company = NULL;
	this->_currentSalary = 0;

	this->_ambition = rand() % 100;
	this->_greed = rand() % 100;
	this->_initiative = rand() % 100;
	this->_creativity = rand() % 100;
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

int Person::getAmbition() {
	return this->_ambition;
}

void Person::setSalary(int amount) {
	this->_currentSalary = amount;
}

int Person::getGreed() {
	return this->_greed;
}

int Person::getInitiative() {
	return this->_initiative;
}

int Person::getCurrentSalary() {
	return this->_currentSalary;
}

bool Person::acceptWages(int money) {
	if (money >= (this->_greed * this->_ambition) * ((rand() % 100) / 100.0))
		return true;
	return false;
}

void Person::addMoney(int money) {
	this->_money += money;
}

int Person::getCreativity() {
	return this->_creativity;
}

Person::~Person() {
}
