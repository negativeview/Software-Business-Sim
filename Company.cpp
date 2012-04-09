#include "Company.h"
#include "Person.h"
#include "Platform.h"
#include "Trait.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Company::Company(const char *name, int money) {
	this->_name = (char *)malloc(strlen(name) + 1);
	strcpy(this->_name, name);
	this->_money = money;
	this->_employees = new list<Person *>();
	this->_knownPeople = new vector<Person *>();
	this->_platformSkills = new map<Platform *, int>();
}

void Company::addEmployee(Person *person) {
	this->_employees->push_back(person);
	this->recomputeCompanySkills();
}

void Company::recomputeCompanySkills() {
	map<Platform *, int> tmpSkillListTotals;
	map<Platform *, int> highestSkill;

	for (list<Person *>::iterator it = this->_employees->begin(); it != this->_employees->end(); ++it) {
		Person *employee = *it;
		map<Platform *, int> *employeePlatformSkills = employee->getPlatformSkills();
		for (map<Platform *, int>::iterator it2 = employeePlatformSkills->begin(); it2 != employeePlatformSkills->end(); ++it2) {
			int existingSkill = tmpSkillListTotals[it2->first];
			existingSkill += it2->second;
			tmpSkillListTotals[it2->first] = existingSkill;

			if (it2->second > highestSkill[it2->first])
				highestSkill[it2->first] = it2->second;
		}
	}

	for (map<Platform *, int>::iterator it3 = tmpSkillListTotals.begin(); it3 != tmpSkillListTotals.end(); ++it3) {
		(*this->_platformSkills)[it3->first] = ((it3->second / this->_employees->size()) + highestSkill[it3->first]) / 2;
	}
}

map<Platform *, int> *Company::getPlatformSkills() {
	return this->_platformSkills;
}

void Company::advanceTime(int time) {
	this->learnAboutEmployees();
}

void Company::learnAboutEmployees() {
	for (vector<Person *>::iterator it = this->_knownPeople->begin(); it != this->_knownPeople->end(); ++it) {
		Person *person = *it;
		if (rand() % 10 == 0) {
			list<Trait *> *allTraits = person->getRealTraits();
			for (list<Trait *>::iterator it2 = allTraits->begin(); it2 != allTraits->end(); ++it2) {
				Trait *t = *it2;
				if (rand() % 10 == 0) {
					t->discoverMore();
				}
			}
		}
	}
}

vector<Person *> *Company::getKnownPeople() {
	return this->_knownPeople;
}

void Company::addKnownPerson(Person *person) {
	this->_knownPeople->push_back(person);
}

void Company::doPayments(int time) {
	// Every two weeks, pay your people.
	int totalPayout = 0;
	if (time % 14 == 0) {
		for (list<Person *>::iterator it = this->_employees->begin(); it != this->_employees->end(); ++it) {
			int salary = (int)((*it)->getCurrentSalary() / 26.0);
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
