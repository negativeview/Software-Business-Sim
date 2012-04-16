#include "Company.h"
#include "InspectCommand.h"
#include "Language.h"
#include "Person.h"
#include "Platform.h"
#include "MasterState.h"
#include "Trait.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InspectCommand::InspectCommand(MasterState *masterState) : CommandFunctor(masterState, "inspect", "Debugging command to give detailed information about a person.") {
	
}

void InspectCommand::executeCommand(const char *line) {
	char *tmp = (char *)malloc(strlen(line) + 1);
	strcpy(tmp, line);

	char *inspect = strtok(tmp, " ");
	char *number = strtok(NULL, " ");

	if (number != NULL) {
		int realNumber = atoi(number);

		vector <Person *> *allPeople = this->_masterState->getPlayerCompany()->getKnownPeople();
		if (realNumber != 0 && realNumber <= allPeople->size()) {
			Person *p = (*allPeople)[realNumber-1];

			printf("%s %s\n", p->getFirstName().c_str(), p->getLastName().c_str());
			printf("\tCompany: %s\n", p->getCompany() ? p->getCompany()->getName() : "None");
			printf("\tSalary: %d\n", p->getCurrentSalary());

			list<Trait *> *realTraits = p->getRealTraits();
			list<Trait *> *believedTraits = p->getBelievedTraits();

			for (list<Trait *>::iterator it = realTraits->begin(); it != realTraits->end(); ++it) {
				Trait *t = *it;
				printf("\tReal %s: %d\n", t->getName().c_str(), t->getAmount());
			}
			for (list<Trait *>::iterator it = believedTraits->begin(); it != believedTraits->end(); ++it) {
				Trait *t = *it;
				printf("\tBelieved %s: %d\n", t->getName().c_str(), t->getAmount());
			}

			map<Platform *, int> *platformSkills = p->getPlatformSkills();
			for (map<Platform *, int>::iterator it = platformSkills->begin(); it != platformSkills->end(); ++it) {
				Platform *p = it->first;
				int amount = it->second;
				printf("\tPlatform %s: %d\n", p->getName().c_str(), amount);
			}

			map<Language *, int> *languageSkills = p->getLanguageSkills();
			for (map<Language *, int>::iterator it = languageSkills->begin(); it != languageSkills->end(); ++it) {
				Language *l = it->first;
				int amount = it->second;
				printf("\tLanguage %s: %d\n", l->getName().c_str(), amount);
			}
		}
	}
	free(tmp);
}

InspectCommand::~InspectCommand() {
	
}