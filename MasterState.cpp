#include "MasterState.h"
#include "CommandList.h"
#include "Company.h"
#include "Language.h"
#include "Market.h"
#include "NameContainer.h"
#include "Person.h"
#include "Platform.h"
#include "Trait.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <string>
using std::string;

MasterState::MasterState() {
	this->_playerCompany = new Company("Testing Corp", 100000);
	this->_allCompanies = new list<Company *>();
	this->_allCompanies->push_back(this->_playerCompany);
	this->_allWorkers = new list<Person *>();
	this->_allConsumers = new list<Person *>();
	this->_time = 0;

	this->_commandList = new CommandList(this);

	this->_messages = new vector<char *>();
	this->_names = new NameContainer();

	this->_allMarkets = new vector<Market *>();
	this->_allMarkets->push_back(new Market("Old People"));

	this->_setupPlatforms();
	this->_setupLanguages();
	this->_setupConsumers();
}

vector<Market *> *MasterState::getMarkets() {
	return this->_allMarkets;
}

vector <char *> *MasterState::getMessages() {
	return this->_messages;
}

void MasterState::clearMessages() {
	for (vector<char *>::iterator it = this->_messages->begin(); it != this->_messages->end(); ++it) {
		char *tmp = *it;
		free(tmp);
	}

	this->_messages->clear();
}

void MasterState::addMessage(const char *message) {
	char *tmp = (char *)malloc(strlen(message) + 1);
	strcpy(tmp, message);
	this->_messages->push_back(tmp);
}


int MasterState::getTime() {
	return this->_time;
}

vector<Platform *> *MasterState::getPlatforms() {
	return this->_allPlatforms;
}

vector<Language *> *MasterState::getLanguages() {
	return this->_allLanguages;
}

Company *MasterState::getPlayerCompany() {
	return this->_playerCompany;
}

list <string> *MasterState::advanceTime(int amount) {
	for (int i = 0; i < amount; i++) {
		this->_time++;

		// One in ten chance of creating a new person.
		if (rand() % (this->_allWorkers->size() + 1) == 0) {
			this->_createWorkers(1);
		}

		for (list<Company *>::iterator it = this->_allCompanies->begin(); it != this->_allCompanies->end(); ++it) {
			Company *c = *it;
			c->doPayments(this->_time);

			for (list<Person *>::iterator it = this->_allWorkers->begin(); it != this->_allWorkers->end(); ++it) {
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

void MasterState::_setupLanguages() {
	this->_allLanguages = new vector<Language *>();
	this->_allLanguages->push_back(new Language("C"));
	this->_allLanguages->push_back(new Language("C++"));
	this->_allLanguages->push_back(new Language("JavaScript"));
	this->_allLanguages->push_back(new Language("Lua"));
	this->_allLanguages->push_back(new Language("Perl"));
	this->_allLanguages->push_back(new Language("PHP"));
	this->_allLanguages->push_back(new Language("Python"));
	this->_allLanguages->push_back(new Language("Ruby"));
}

void MasterState::_setupPlatforms() {
	this->_allPlatforms = new vector<Platform *>();
	this->_allPlatforms->push_back(new Platform("Browser"));
	this->_allPlatforms->push_back(new Platform("Console"));
	this->_allPlatforms->push_back(new Platform("Desktop"));
	this->_allPlatforms->push_back(new Platform("Mobile"));
	this->_allPlatforms->push_back(new Platform("Server"));
}


void MasterState::_setupConsumers() {
	for (int i = 0; i < 500; i++) {
		string firstName = this->_names->getFirstName();
		string lastName = this->_names->getLastName();

		int money = rand() % 100000;

		Person *p = new Person(firstName, lastName, money);

		for (vector<Platform *>::iterator it = this->_allPlatforms->begin(); it != this->_allPlatforms->end(); ++it) {
			p->setPlatformSkill(*it, rand() % 100);
		}

		for (vector<Language *>::iterator it2 = this->_allLanguages->begin(); it2 != this->_allLanguages->end(); ++it2) {
			p->setLanguageSkill(*it2, rand() % 100);
		}

		this->_allConsumers->push_back(p);
	}
}

void MasterState::_createWorkers(int count) {
	for (int i = 0; i < count; i++) {
		string firstName = this->_names->getFirstName();
		string lastName = this->_names->getLastName();

		int money = rand() % 100000;

		char message[100];
		sprintf(message, "%s %s applied for a job.", firstName.c_str(), lastName.c_str());

		this->addMessage(message);
		Person *p = new Person(firstName, lastName, money);

		for (vector<Platform *>::iterator it = this->_allPlatforms->begin(); it != this->_allPlatforms->end(); ++it) {
			p->setPlatformSkill(*it, rand() % 100);
		}

		for (vector<Language *>::iterator it2 = this->_allLanguages->begin(); it2 != this->_allLanguages->end(); ++it2) {
			p->setLanguageSkill(*it2, rand() % 100);
		}

		this->_allWorkers->push_back(p);
	}
}

void MasterState::executeCommand(const char *command) {
	this->_commandList->executeCommand(command);
}

MasterState::~MasterState() {
	delete this->_playerCompany;
	this->_playerCompany = NULL;
	delete this->_allCompanies;
	this->_allCompanies = NULL;

	for (list<Person *>::iterator allWorkersIterator = this->_allWorkers->begin(); allWorkersIterator != this->_allWorkers->end(); ++allWorkersIterator) {
		Person *p = *allWorkersIterator;
		delete p;
	}
	delete this->_allWorkers;
	this->_allWorkers = NULL;

	for (list<Person *>::iterator allConsumersIterator = this->_allConsumers->begin(); allConsumersIterator != this->_allConsumers->end(); ++allConsumersIterator) {
		Person *p = *allConsumersIterator;
		delete p;
	}
	delete this->_allConsumers;
	this->_allConsumers = NULL;

	for (vector<Platform *>::iterator platformIterator = this->_allPlatforms->begin(); platformIterator != this->_allPlatforms->end(); ++platformIterator) {
		Platform *platform = *platformIterator;
		delete platform;
	}
	delete this->_allPlatforms;
	this->_allPlatforms = NULL;
	delete this->_playerCompany;
	this->_playerCompany = NULL;
}