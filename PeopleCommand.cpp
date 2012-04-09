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

PeopleCommand::PeopleCommand(MasterState *masterState) : CommandFunctor(masterState, "people", "Tells you information about known people.") {
	
}

void PeopleCommand::executeCommand(const char *line) {
	int index = 0;

	vector<Person *> *allPeople = this->_masterState->getPlayerCompany()->getKnownPeople();

	for (vector<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		++index;
		Person *currentPerson = *it;
		cout << index << ": " << currentPerson->getFirstName() << " " << currentPerson->getLastName();
		
		Company *company = currentPerson->getCompany();
		
		if (company)
			printf(" (%s)", currentPerson->getCompany()->getName());

		list<Trait *> *personTraits;
		if (company && company == this->_masterState->getPlayerCompany())
			personTraits = currentPerson->getRealTraits();
		else
			personTraits = currentPerson->getBelievedTraits();

		for (list<Trait *>::iterator it2 = personTraits->begin(); it2 != personTraits->end(); ++it2) {
			Trait *t = *it2;
			printf("\n   %10s: %s", t->getName().c_str(), t->getDiscoveryModifiedText().c_str());
		}
		printf("\n");
	}
}

PeopleCommand::~PeopleCommand() {
	
}