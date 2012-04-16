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
	list<Person *> *employees = playerCompany->getEmployees();
	vector<Project *> *projects = playerCompany->getProjects();
	map<Platform *, int> *platformSkills = playerCompany->getPlatformSkills();

	this->_masterState->addMessage(
		"You currently have %d money"
	);
	this->_masterState->addMessage(
		"You have %lu employees"
	);
	this->_masterState->addMessage(
		"You have %lu projects"
	);
	this->_masterState->addMessage("Your skills in platforms are as follows:");
	for (map<Platform *, int>::iterator it = platformSkills->begin(); it != platformSkills->end(); ++it) {
		this->_masterState->addMessage(
			"\t%s: %d"
		);
		//printf("\t%s: %d\n", it->first->getName().c_str(), it->second);
	}
}

StatusCommand::~StatusCommand() {
	
}