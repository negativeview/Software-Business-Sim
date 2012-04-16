#include "Company.h"
#include "PeopleCommand.h"
#include "Person.h"
#include "MasterState.h"
#include "Trait.h"

#include <stdio.h>

#include <vector>
using std::vector;

#include <iostream>
using std::cout;

PeopleCommand::PeopleCommand(MasterState *masterState) : CommandFunctor(masterState, "applicants", "Tells you information about known people.") {
	
}

void PeopleCommand::executeCommand(const char *line) {
	int index = 0;

	vector<Person *> *allPeople = this->_masterState->getPlayerCompany()->getKnownPeople();

	for (vector<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		++index;
		Person *currentPerson = *it;

		char message[100];

		sprintf(message, "%03d: %s %s", index, currentPerson->getFirstName().c_str(), currentPerson->getLastName().c_str());
		this->_masterState->addMessage(message);
		
		Company *company = currentPerson->getCompany();
		
		list<Trait *> *personTraits;
		if (company && company == this->_masterState->getPlayerCompany())
			personTraits = currentPerson->getRealTraits();
		else
			personTraits = currentPerson->getBelievedTraits();

		for (list<Trait *>::iterator it2 = personTraits->begin(); it2 != personTraits->end(); ++it2) {
			Trait *t = *it2;
			sprintf(message, "    %10s: %s", t->getName().c_str(), t->getDiscoveryModifiedText().c_str());
			this->_masterState->addMessage(message);
		}
	}
}

PeopleCommand::~PeopleCommand() {
	
}