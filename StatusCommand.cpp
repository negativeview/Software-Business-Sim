#include "Company.h"
#include "Language.h"
#include "StatusCommand.h"
#include "MasterState.h"
#include "Platform.h"

#include <stdio.h>

#include <vector>
using std::vector;

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

	this->_masterState->addMessage("Your skills in platforms are as follows:");
	for (map<Platform *, int>::iterator it = platformSkills->begin(); it != platformSkills->end(); ++it) {
		sprintf(message, "\t%s: %d", it->first->getName().c_str(), it->second);
		this->_masterState->addMessage(message);
	}
}

StatusCommand::~StatusCommand() {
	
}