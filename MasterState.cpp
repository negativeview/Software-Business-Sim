#include "MasterState.h"
#include "Company.h"
#include "Person.h"
#include "Platform.h"
#include "Trait.h"

#include <stdlib.h>
#include <stdio.h>

MasterState::MasterState() {
	this->_playerCompany = new Company("Testing Corp", 100000);
	this->_allCompanies = new list<Company *>();
	this->_allCompanies->push_back(this->_playerCompany);
	this->_allPeople = new list<Person *>();
	this->_time = 0;

	this->_setupFirstNames();
	this->_setupLastNames();
	this->_setupPlatforms();

	this->_createPeople(5);
}

Company *MasterState::getPlayerCompany() {
	return this->_playerCompany;
}

list <string> *MasterState::advanceTime(int amount) {
	for (int i = 0; i < amount; i++) {
		this->_time++;

		// One in ten chance of creating a new person.
		if (rand() % 10 == 0) {
			this->_createPeople(1);
		}

		for (list<Company *>::iterator it = this->_allCompanies->begin(); it != this->_allCompanies->end(); ++it) {
			Company *c = *it;
			c->doPayments(this->_time);

			for (list<Person *>::iterator it = this->_allPeople->begin(); it != this->_allPeople->end(); ++it) {
				int found = 0;
				vector<Person *> *knownPeople = c->getKnownPeople();
				for (vector<Person *>::iterator it2 = knownPeople->begin(); it2 != knownPeople->end(); ++it2) {
					if (*it == *it2) {
						found = 1;
						break;
					}
				}
				if (found == 0) {
					// Every person that's not already known has a 1 in 10
					// chance of becoming discovered by the company. This number
					// needs to be tweaked as it causes way too many employees
					// too early.
					if (rand() % 10) {
						c->addKnownPerson(*it);
					}
				}
			}

			c->advanceTime(this->_time);
		}
	}
}

void MasterState::_setupPlatforms() {
	this->_allPlatforms = new vector<Platform *>();
	this->_allPlatforms->push_back(new Platform("desktop"));
	this->_allPlatforms->push_back(new Platform("browser"));
	this->_allPlatforms->push_back(new Platform("console"));
	this->_allPlatforms->push_back(new Platform("mobile"));
	this->_allPlatforms->push_back(new Platform("server"));
}

void MasterState::_setupLastNames() {
	this->_lastNames = new vector<string>();
	this->_lastNames->push_back("Anderson");
	this->_lastNames->push_back("Anniston");
	this->_lastNames->push_back("Gohde");
	this->_lastNames->push_back("Grace");
	this->_lastNames->push_back("Miller");
	this->_lastNames->push_back("Pepper");
	this->_lastNames->push_back("Seemann");
	this->_lastNames->push_back("Wolever");
}

void MasterState::_setupFirstNames() {
	this->_firstNames = new vector<string>();
	this->_firstNames->push_back("Alice");
	this->_firstNames->push_back("Barbara");
	this->_firstNames->push_back("Brianna");
	this->_firstNames->push_back("Charles");
	this->_firstNames->push_back("Christopher");
	this->_firstNames->push_back("Daniel");
	this->_firstNames->push_back("David");
	this->_firstNames->push_back("Donald");
	this->_firstNames->push_back("Elizabeth");
	this->_firstNames->push_back("James");
	this->_firstNames->push_back("Jennifer");
	this->_firstNames->push_back("Jeremy");
	this->_firstNames->push_back("John");
	this->_firstNames->push_back("Joseph");
	this->_firstNames->push_back("Julia");
	this->_firstNames->push_back("Linda");
	this->_firstNames->push_back("Maria");
	this->_firstNames->push_back("Markus");
	this->_firstNames->push_back("Mark");
	this->_firstNames->push_back("Mary");
	this->_firstNames->push_back("Michael");
	this->_firstNames->push_back("Patricia");
	this->_firstNames->push_back("Paul");
	this->_firstNames->push_back("Richard");
	this->_firstNames->push_back("Robert");
	this->_firstNames->push_back("Susan");
	this->_firstNames->push_back("Thomas");
	this->_firstNames->push_back("William");
}

void MasterState::_createPeople(int count) {
	for (int i = 0; i < count; i++) {
		string firstName = this->_getRandomName(this->_firstNames);
		string lastName = this->_getRandomName(this->_lastNames);
		int money = rand() % 100000;

		Person *p = new Person(firstName, lastName, money);

		for (vector<Platform *>::iterator it = this->_allPlatforms->begin(); it != this->_allPlatforms->end(); ++it) {
			p->setPlatformSkill(*it, rand() % 100);
		}

		this->_allPeople->push_back(p);
	}
}


string MasterState::_getRandomName(vector<string> *nameList) {
	int length = nameList->size();
	int element = rand() % length;

	string ret = (*nameList)[element];
	return ret;
}

MasterState::~MasterState() {
	delete this->_playerCompany;
	this->_playerCompany = NULL;
	delete this->_allCompanies;
	this->_allCompanies = NULL;

	for (list<Person *>::iterator allPeopleIterator = this->_allPeople->begin(); allPeopleIterator != this->_allPeople->end(); ++allPeopleIterator) {
		Person *p = *allPeopleIterator;
		delete p;
	}
	delete this->_allPeople;
	this->_allPeople = NULL;

	for (vector<Platform *>::iterator platformIterator = this->_allPlatforms->begin(); platformIterator != this->_allPlatforms->end(); ++platformIterator) {
		Platform *platform = *platformIterator;
		delete platform;
	}
	delete this->_allPlatforms;
	this->_allPlatforms = NULL;
	delete this->_lastNames;
	this->_lastNames = NULL;
	delete this->_firstNames;
	this->_firstNames = NULL;
	delete this->_playerCompany;
	this->_playerCompany = NULL;
}