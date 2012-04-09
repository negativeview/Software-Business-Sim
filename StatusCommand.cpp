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
	map<Platform *, int> *platformSkills = playerCompany->getPlatformSkills();

	printf("You current have %d money.\n", money);
	printf("You have %d employees.\n", employees->size());
	printf("Your skills in platforms are as follows:\n");
	for (map<Platform *, int>::iterator it = platformSkills->begin(); it != platformSkills->end(); ++it) {
		printf("\t%s: %d\n", it->first->getName().c_str(), it->second);
	}

	map<Language *, int> *languageSkills = playerCompany->getLanguageSkills();
	printf("Your skills in languages are as follows:\n");
	for (map<Language *, int>::iterator it2 = languageSkills->begin(); it2 != languageSkills->end(); ++it2) {
		Language *l = it2->first;
		int skill = it2->second;
		printf("\t%s: %d\n", l->getName().c_str(), skill);
	}
}

StatusCommand::~StatusCommand() {
	
}