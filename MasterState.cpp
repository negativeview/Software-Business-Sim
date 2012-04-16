#include "MasterState.h"
#include "Company.h"
#include "HelpCommand.h"
#include "HireCommand.h"
#include "Language.h"
#include "linenoise.h"
#include "QuitCommand.h"
#include "PeopleCommand.h"
#include "Person.h"
#include "Platform.h"
#include "ProjectCommand.h"
#include "StatusCommand.h"
#include "Trait.h"
#include "WaitCommand.h"

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

	this->_messages = new vector<char *>();

	this->_setupFirstNames();
	this->_setupLastNames();
	this->_setupPlatforms();
	this->_setupLanguages();
	this->_setupCommands();
	this->_setupConsumers();

	this->_createWorkers(5);
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
	char *tmp = (char *)malloc(strlen(message));
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
		if (rand() % 10 == 0) {
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

void MasterState::_setupLastNames() {
	this->_lastNames = new vector<string>();
	this->_lastNames->push_back("Amundson");
	this->_lastNames->push_back("Anderson");
	this->_lastNames->push_back("Anniston");
	this->_lastNames->push_back("Birthler");
	this->_lastNames->push_back("Bremer");
	this->_lastNames->push_back("Cannon");
	this->_lastNames->push_back("Compton");
	this->_lastNames->push_back("Dorland");
	this->_lastNames->push_back("Esbensen");
	this->_lastNames->push_back("Frazier");
	this->_lastNames->push_back("Gemoets");
	this->_lastNames->push_back("Gloege");
	this->_lastNames->push_back("Gohde");
	this->_lastNames->push_back("Grace");
	this->_lastNames->push_back("Green");
	this->_lastNames->push_back("Hemmingway");
	this->_lastNames->push_back("Jones");
	this->_lastNames->push_back("Kamke");
	this->_lastNames->push_back("Koehl");
	this->_lastNames->push_back("Lamb");
	this->_lastNames->push_back("Mars");
	this->_lastNames->push_back("Mason");
	this->_lastNames->push_back("Miller");
	this->_lastNames->push_back("Myers");
	this->_lastNames->push_back("Olson");
	this->_lastNames->push_back("Pepper");
	this->_lastNames->push_back("Poeschl");
	this->_lastNames->push_back("Reed");
	this->_lastNames->push_back("Reynolds");
	this->_lastNames->push_back("Runyon");
	this->_lastNames->push_back("Schilken");
	this->_lastNames->push_back("Schneider");
	this->_lastNames->push_back("Seemann");
	this->_lastNames->push_back("Simula");
	this->_lastNames->push_back("Smith");
	this->_lastNames->push_back("Spradlin");
	this->_lastNames->push_back("Tava");
	this->_lastNames->push_back("Wade");
	this->_lastNames->push_back("Wolever");
	this->_lastNames->push_back("Wurm");
}

void MasterState::_setupFirstNames() {
	this->_firstNames = new vector<string>();
	this->_firstNames->push_back("Aaron");
	this->_firstNames->push_back("Albert");
	this->_firstNames->push_back("Alice");
	this->_firstNames->push_back("Amanda");
	this->_firstNames->push_back("Antoinette");
	this->_firstNames->push_back("Barbara");
	this->_firstNames->push_back("Ben");
	this->_firstNames->push_back("Brad");
	this->_firstNames->push_back("Breen");
	this->_firstNames->push_back("Brianna");
	this->_firstNames->push_back("Charles");
	this->_firstNames->push_back("Chelsea");
	this->_firstNames->push_back("Christopher");
	this->_firstNames->push_back("Dan");
	this->_firstNames->push_back("Daniel");
	this->_firstNames->push_back("Dave");
	this->_firstNames->push_back("David");
	this->_firstNames->push_back("Devin");
	this->_firstNames->push_back("Donald");
	this->_firstNames->push_back("Elizabeth");
	this->_firstNames->push_back("Erica");
	this->_firstNames->push_back("Eve");
	this->_firstNames->push_back("Gary");
	this->_firstNames->push_back("Gillian");
	this->_firstNames->push_back("Gina");
	this->_firstNames->push_back("Greg");
	this->_firstNames->push_back("Hannah");
	this->_firstNames->push_back("James");
	this->_firstNames->push_back("Jamie");
	this->_firstNames->push_back("Jenna");
	this->_firstNames->push_back("Jennifer");
	this->_firstNames->push_back("Jeremy");
	this->_firstNames->push_back("John");
	this->_firstNames->push_back("Joseph");
	this->_firstNames->push_back("Julia");
	this->_firstNames->push_back("Linda");
	this->_firstNames->push_back("Lisa");
	this->_firstNames->push_back("Maria");
	this->_firstNames->push_back("Markus");
	this->_firstNames->push_back("Mark");
	this->_firstNames->push_back("Mary");
	this->_firstNames->push_back("Matt");
	this->_firstNames->push_back("Matthew");
	this->_firstNames->push_back("Michael");
	this->_firstNames->push_back("Patricia");
	this->_firstNames->push_back("Paul");
	this->_firstNames->push_back("Richard");
	this->_firstNames->push_back("Robert");
	this->_firstNames->push_back("Susan");
	this->_firstNames->push_back("Thomas");
	this->_firstNames->push_back("William");
}

void MasterState::_setupConsumers() {
	for (int i = 0; i < 500; i++) {
		string firstName = this->_getRandomName(this->_firstNames);
		string lastName = this->_getRandomName(this->_lastNames);
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
		string firstName = this->_getRandomName(this->_firstNames);
		string lastName = this->_getRandomName(this->_lastNames);
		int money = rand() % 100000;

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
	if (command[0] != '\0') {
		int found = 0;
		for (vector<CommandFunctor *>::iterator it = this->_allCommands->begin(); it != this->_allCommands->end(); ++it) {
			CommandFunctor *commandFunctor = *it;
			string prefix = commandFunctor->getPrefix();

			if (strncmp(prefix.c_str(), command, strlen(prefix.c_str())) == 0) {
				commandFunctor->executeCommand(command);
				linenoiseHistoryAdd(command);
				linenoiseHistorySave("history.txt");
				return;
			}
		}
	}
}

void MasterState::_setupCommands() {
	this->_allCommands = new vector<CommandFunctor *>();
	this->_allCommands->push_back(new HelpCommand(this));
	this->_allCommands->push_back(new StatusCommand(this));
	this->_allCommands->push_back(new PeopleCommand(this));
	this->_allCommands->push_back(new ProjectCommand(this));
	this->_allCommands->push_back(new HireCommand(this));
	this->_allCommands->push_back(new WaitCommand(this));
	this->_allCommands->push_back(new QuitCommand(this));
}

vector<CommandFunctor *> *MasterState::getCommands() {
	return this->_allCommands;
}

/*
void MasterState::setNextHandler(void (*next_handler)(MasterState *masterState, const char *line)) {
	this->_next_handler_pointer = next_handler;
}

void (*)(MasterState *masterState, const char *line) *MasterState::getNextHandler() {
	return this->_next_handler_pointer;
}
*/

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
	delete this->_lastNames;
	this->_lastNames = NULL;
	delete this->_firstNames;
	this->_firstNames = NULL;
	delete this->_playerCompany;
	this->_playerCompany = NULL;
}