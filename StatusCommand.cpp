#include "Company.h"
#include "Language.h"
#include "StatusCommand.h"
#include "Market.h"
#include "MasterState.h"
#include "Platform.h"
#include "Project.h"

#include <stdio.h>

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

StatusCommand::StatusCommand(MasterState *masterState) : CommandFunctor(masterState, "status", "Get a summary of how you are doing. No time passes.") {
	
}

void StatusCommand::executeCommand(const char *line) {
	Company *playerCompany = this->_masterState->getPlayerCompany();
	int money = playerCompany->getMoney();
	vector<Person *> *employees = playerCompany->getEmployees();
	vector<Project *> *projects = playerCompany->getProjects();
	map<Platform *, int> *platformSkills = playerCompany->getPlatformSkills();

	char message[100];
	sprintf(message, "You currently have %d money", money);
	this->_masterState->addMessage(message);

	sprintf(message, "You have %lu employees", employees->size());
	this->_masterState->addMessage(message);

	sprintf(message, "You have %lu projects", projects->size());
	this->_masterState->addMessage(message);

	map<string, int> *score = new map<string, int>();
	for (vector<Project *>::iterator it = projects->begin(); it != projects->end(); ++it) {
		Project *p = *it;

		Platform *platform = p->getPlatform();
		map<string, int> *requirements = platform->getRequires();
		for (map<string, int>::iterator it2 = requirements->begin(); it2 != requirements->end(); ++it2) {
			(*score)[it2->first] -= it2->second;
		}
		map<string, int> *provides = platform->getProvides();
		for(map<string, int>::iterator it2 = provides->begin(); it2 != provides->end(); ++it2) {
			(*score)[it2->first] += it2->second;
		}

		sprintf(message, "\t%s-based %s for %s\n", platform->getFullName(), p->getLanguage()->getFullName(), p->getMarket()->getFullName());
		this->_masterState->addMessage(message);

		for(map<string, int>::iterator it2 = score->begin(); it2 != score->end(); ++it2) {
			sprintf(message, "\t%s: %d\n", it2->first.c_str(), it2->second);
			this->_masterState->addMessage(message);
		}

	}

	this->_masterState->addMessage("Your skills in platforms are as follows:");
	for (map<Platform *, int>::iterator it = platformSkills->begin(); it != platformSkills->end(); ++it) {
		sprintf(message, "\t%s: %d", it->first->getName().c_str(), it->second);
		this->_masterState->addMessage(message);
	}
}

StatusCommand::~StatusCommand() {
	
}