#include "AmbitionTrait.h"
#include "Company.h"
#include "CreativityTrait.h"
#include "GreedTrait.h"
#include "InitiativeTrait.h"
#include "Person.h"
#include "Platform.h"

#include <stdlib.h>
#include <stdio.h>

Person::Person(string firstName, string lastName, int money) {
	this->_firstName = firstName;
	this->_lastName = lastName;
	this->_money = money;
	this->_company = NULL;
	this->_currentSalary = 0;

	this->_platformSkills = new map<Platform *, int>();

	this->_actualTraits = new list<Trait *>();
	this->_actualTraits->push_back(new AmbitionTrait(rand() % 100));
	this->_actualTraits->push_back(new GreedTrait(rand() % 100));
	this->_actualTraits->push_back(new InitiativeTrait(rand() % 100));
	this->_actualTraits->push_back(new CreativityTrait(rand() % 100));

	this->_believedTraits = new list<Trait *>();
	this->_believedTraits->push_back(new AmbitionTrait(rand() % 100));
	this->_believedTraits->push_back(new GreedTrait(rand() % 100));
	this->_believedTraits->push_back(new InitiativeTrait(rand() % 100));
	this->_believedTraits->push_back(new CreativityTrait(rand() % 100));
}

Company *Person::getCompany() {
	return this->_company;
}

map<Platform *, int> *Person::getPlatformSkills() {
	return this->_platformSkills;
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

void Person::setSalary(int amount) {
	this->_currentSalary = amount;
}

int Person::getCurrentSalary() {
	return this->_currentSalary;
}

bool Person::acceptWages(int money) {
	int traitInfluence = 0;
	for (list<Trait *>::iterator it = this->_believedTraits->begin(); it != this->_believedTraits->end(); ++it) {
		traitInfluence += (*it)->influenceOnSalaryRequirements();
	}

	float randomInfluence = ((rand() % 100) / 100.0);

	if (money >= traitInfluence * randomInfluence)
		return true;
	return false;
}

void Person::setPlatformSkill(Platform *platform, int skill) {
	(*this->_platformSkills)[platform] = skill;
}

list<Trait *> *Person::getRealTraits() {
	return this->_actualTraits;
}

list <Trait *> *Person::getBelievedTraits() {
	return this->_believedTraits;
}

void Person::addMoney(int money) {
	this->_money += money;
}

Person::~Person() {
}
