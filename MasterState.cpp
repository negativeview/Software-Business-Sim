#include "MasterState.h"
#include "Company.h"
#include "Person.h"
#include "Trait.h"

#include <stdlib.h>
#include <stdio.h>

MasterState::MasterState() {
	this->_playerCompany = new Company("Testing Corp", 100000);
	this->_allCompanies = new list<Company *>();
	this->_allPeople = new list<Person *>();
	this->_knownPeople = new vector<Person *>();
	this->_time = 0;

	this->_setupFirstNames();
	this->_setupLastNames();

	this->_createPeople(5);
}

Company *MasterState::getPlayerCompany() {
	return this->_playerCompany;
}

vector <Person *> *MasterState::getKnownPeople() {
	return this->_knownPeople;
}

list <string> *MasterState::advanceTime(int amount) {
	for (int i = 0; i < amount; i++) {
		this->_time++;

		// One in ten chance of creating a new person.
		if (rand() % 10 == 0) {
			this->_createPeople(1);
		}

		// Every two weeks, pay your people.
		int totalPayout = 0;
		if (this->_time % 14 == 0) {
			list<Person *> *employees = this->_playerCompany->getEmployees();
			for (list<Person *>::iterator it = employees->begin(); it != employees->end(); ++it) {
				int salary = (*it)->getCurrentSalary();
				this->_playerCompany->payWages(salary);
				(*it)->addMoney(salary);
				totalPayout += salary;
			}
			printf("Day %03d: Payed %d in salaries.\n", this->_time, totalPayout);
		}

		int overheadCost = this->_playerCompany->getOverheadCost();
		printf("Day %03d: Payed %d in random costs.\n", this->_time, overheadCost);
		this->_playerCompany->payOverhead(overheadCost);

		// Possibly/probably insert people into the known list.
		for (list<Person *>::iterator it = this->_allPeople->begin(); it != this->_allPeople->end(); ++it) {
			int found = 0;
			for (vector<Person *>::iterator it2 = this->_knownPeople->begin(); it2 != this->_knownPeople->end(); ++it2) {
				if (*it == *it2) {
					found = 1;
					break;
				}
			}
			if (found == 0) {
				if (rand() % 10) {
					this->_knownPeople->push_back(*it);
					printf("Day %03d: Discovered %s %s\n", this->_time, (*it)->getFirstName().c_str(), (*it)->getLastName().c_str());
				}
			}
		}

		for (vector<Person *>::iterator it = this->_knownPeople->begin(); it != this->_knownPeople->end(); ++it) {
			Person *person = *it;
			if (rand() % 10 == 0) {
				list<Trait *> *allTraits = person->getTraits();
				for (list<Trait *>::iterator it2 = allTraits->begin(); it2 != allTraits->end(); ++it2) {
					Trait *t = *it2;
					if (rand() % 10 == 0) {
						t->discoverMore();
						printf("Day %03d: Learned more about the %s of %s %s\n", this->_time, t->getName().c_str(), person->getFirstName().c_str(), person->getLastName().c_str());
					}
				}
			}
		}
	}
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
		this->_allPeople->push_back(new Person(firstName, lastName, money));
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
	delete this->_allPeople;
	this->_allPeople = NULL;
	delete this->_knownPeople;
	this->_knownPeople = NULL;
}