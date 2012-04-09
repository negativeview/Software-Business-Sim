#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise.h"
#include "Company.h"
#include "Language.h"
#include "MasterState.h"
#include "Person.h"
#include "Platform.h"
#include "Trait.h"

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <iostream>
using std::cout;

struct command {
	const char *shortName;

	void (*callback)(MasterState *masterState, const char *);
	const char *fullDesc;
	void (*furtherOptions)(MasterState *masterState, linenoiseCompletions *lc, const char *);
};

MasterState *masterState;

int main(int argc, char *argv[]) {
	char *line;

	srand(time(NULL));
	masterState = new MasterState();

	printf("Congratulations!\n\n");
	printf("You are the proud CEO of a brand new company: %s\n\n", masterState->getPlayerCompany()->getName());
	printf("You must make the best software (and the most money) using what you have been given.\n\n");

	linenoiseHistoryLoad("history.txt");

	// Advance time by 10 days just so something interesting might happen.
	masterState->advanceTime(10);

	while((line = linenoise("command> ")) != NULL) {
		masterState->executeCommand(line);
		free(line);

		int moneyLeft = masterState->getPlayerCompany()->getMoney();
		printf("You have %d money left\n", moneyLeft);
		if (moneyLeft <= 0) {
			printf("You have lost.\n");
			delete masterState;
			return 0;
		}
	}
	return 0;
}

void status_function(MasterState *masterState, const char *line) {
	Company *playerCompany = masterState->getPlayerCompany();
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

void wait_function(MasterState *masterState, const char *line) {
	masterState->advanceTime(7);
}

void hire_function(MasterState *masterState, const char *line) {
	char *tmp = (char *)malloc(strlen(line) + 1);
	strcpy(tmp, line);

	char *hire = strtok(tmp, " ");
	char *number = strtok(NULL, " ");
	char *salary = strtok(NULL, " ");

	if (number != NULL && salary != NULL) {
		int realNumber = atoi(number);
		int realSalary = atoi(salary);

		vector <Person *> *allPeople = masterState->getPlayerCompany()->getKnownPeople();
		if (realNumber != 0 && salary != 0 && realNumber <= allPeople->size()) {
			Person *p = (*allPeople)[realNumber-1];
			if (p->acceptWages(realSalary)) {
				p->hire(masterState->getPlayerCompany());
				masterState->getPlayerCompany()->addEmployee(p);
				p->setSalary(realSalary);
			} else {
				printf("%s %s rejected your offer\n", p->getFirstName().c_str(), p->getLastName().c_str());
			}

			// Hiring people takes time.
			masterState->advanceTime(1);
			free(tmp);
			return;
		}
	}
	free(tmp);
}

void choose_target_platform(MasterState *masterState, const char *line) {
	printf("Here, yay!");
}

void project_function(MasterState *masterState, const char *line) {
	vector<Platform *> *platforms = masterState->getPlatforms();
	map<Platform *, int> *platformSkills = masterState->getPlayerCompany()->getPlatformSkills();

	printf("Pick a target platform:\n");
	int index = 0;
	for (vector<Platform *>::iterator it = platforms->begin(); it != platforms->end(); ++it) {
		Platform *p = *it;
		++index;
		printf("\t%3d: %s [Company skill: %d]\n", index, p->getName().c_str(), (*platformSkills)[p]);
	}

	//masterState->setNextHandler(choose_target_platform);
}

void people_function(MasterState *masterState, const char *line) {
	int index = 0;

	vector<Person *> *allPeople = masterState->getPlayerCompany()->getKnownPeople();

	for (vector<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		++index;
		Person *currentPerson = *it;
		cout << index << ": " << currentPerson->getFirstName() << " " << currentPerson->getLastName();
		
		Company *company = currentPerson->getCompany();
		
		if (company)
			printf(" (%s)", currentPerson->getCompany()->getName());

		list<Trait *> *personTraits;
		if (company && company == masterState->getPlayerCompany())
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