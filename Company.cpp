#include "Company.h"
#include "Language.h"
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
	this->_languageSkills = new map<Language *, int>();
	this->_allProjects = new vector<Project *>();
}

vector<Project *> *Company::getProjects() {
	return this->_allProjects;
}

void Company::addProject(Project *p) {
	this->_allProjects->push_back(p);
}

void Company::addEmployee(Person *person) {
	this->_employees->push_back(person);
	this->recomputeCompanySkills();

	for (vector<Person *>::iterator it = this->_knownPeople->begin(); it != this->_knownPeople->end(); ++it) {
		Person *p = *it;
		if (p == person) {
			this->_knownPeople->erase(it);
			return;
		}
	}
}

/**
 * Companies, just like people have skills. The skill of a company is based on
 * the skill of the employees, but it's not a simple summing. No no, here's
 * where some OMG biting comentary comes in. The formula is actually thus:
 *
 * average(maximum + average)
 *
 * That is, I take the average skill across all employees, add it to the maximum
 * skill of all employees, and divide by two. This isn't *exactly* what I want,
 * but it's the closest simple formula I've found. It satisfies my two biggest
 * desires for this function:
 *
 * 1) Adding an idiot lowers the skill level, not increases it.
 * 2) Adding someone smarter than all other employees raises the skill level.
 */
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

	map<Language *, int> tmpLanguageListTotals;
	map<Language *, int> highestLanguage;

	for (list<Person *>::iterator it = this->_employees->begin(); it != this->_employees->end(); ++it) {
		Person *employee = *it;
		map<Language *, int> *employeeLanguageSkills = employee->getLanguageSkills();
		for (map<Language *, int>::iterator it2 = employeeLanguageSkills->begin(); it2 != employeeLanguageSkills->end(); ++it2) {
			int existingSkill = tmpLanguageListTotals[it2->first];
			existingSkill += it2->second;
			tmpLanguageListTotals[it2->first] = existingSkill;

			if (it2->second > highestLanguage[it2->first])
				highestLanguage[it2->first] = it2->second;
		}
	}

	for (map<Language *, int>::iterator it3 = tmpLanguageListTotals.begin(); it3 != tmpLanguageListTotals.end(); ++it3) {
		(*this->_languageSkills)[it3->first] = ((it3->second / this->_employees->size()) + highestLanguage[it3->first]) / 2;
	}
}

map<Platform *, int> *Company::getPlatformSkills() {
	return this->_platformSkills;
}

map<Language *, int> *Company::getLanguageSkills() {
	return this->_languageSkills;
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
	for (list<Person *>::iterator it = this->_employees->begin(); it != this->_employees->end(); ++it) {
		Person *p = *it;
		if (p == person)
			return;
	}
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
	delete this->_platformSkills;
	this->_platformSkills = NULL;
	delete this->_knownPeople;
	this->_knownPeople = NULL;
}
