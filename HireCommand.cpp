#include "Company.h"
#include "HireCommand.h"
#include "MasterState.h"
#include "Person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
using std::vector;

HireCommand::HireCommand(MasterState *masterState) : CommandFunctor(masterState, "hire", "Hire an employee to work in your business.") {
	
}

void HireCommand::executeCommand(const char *line) {
	char *tmp = (char *)malloc(strlen(line) + 1);
	strcpy(tmp, line);

	char *hire = strtok(tmp, " ");
	char *number = strtok(NULL, " ");
	char *salary = strtok(NULL, " ");

	if (number != NULL && salary != NULL) {
		int realNumber = atoi(number);
		int realSalary = atoi(salary);

		vector <Person *> *allPeople = this->_masterState->getPlayerCompany()->getKnownPeople();
		if (realNumber != 0 && salary != 0 && realNumber <= allPeople->size()) {
			Person *p = (*allPeople)[realNumber-1];
			if (p->acceptWages(realSalary)) {
				p->hire(this->_masterState->getPlayerCompany());
				this->_masterState->getPlayerCompany()->addEmployee(p);
				p->setSalary(realSalary);
			} else {
				printf("%s %s rejected your offer\n", p->getFirstName().c_str(), p->getLastName().c_str());
			}

			// Hiring people takes time.
			this->_masterState->advanceTime(1);
			free(tmp);
			return;
		}
	}
	free(tmp);
}

HireCommand::~HireCommand() {
	
}