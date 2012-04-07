#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise.h"
#include "Company.h"
#include "Person.h"
#include "MasterState.h"

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

void help_function(MasterState *masterState, const char *);
void quit_function(MasterState *masterState, const char *);
void wait_function(MasterState *masterState, const char *);
void hire_function(MasterState *masterState, const char *);
void hire_autocomplete(MasterState *masterState, linenoiseCompletions *lc, const char *);
void people_function(MasterState *masterState, const char *);
list <Person *> *createPeople();

struct command commands[] = {
	{
		"help",
		help_function,
		"Lists the commands that are available.",
		NULL
	},
	{
		"quit",
		quit_function,
		"Quits the game.",
		NULL
	},
	{
		"people",
		people_function,
		"Shows all the people that exist in this world.",
		NULL,
	},
	{
		"hire",
		hire_function,
		"Hires a new employee.",
		hire_autocomplete
	},
	{
		"wait",
		wait_function,
		"Waits for a week.",
		NULL
	}
};
int num_commands = 5;

MasterState *masterState;

void completion(const char *buf, linenoiseCompletions *lc) {
	for (int i = 0; i < num_commands; i++) {
		struct command currentCommand = commands[i];
		if (strncmp(buf, currentCommand.shortName, strlen(buf)) == 0) {
			linenoiseAddCompletion(lc, currentCommand.shortName);
		}

		if (currentCommand.furtherOptions != NULL) {
			currentCommand.furtherOptions(masterState, lc, buf);
		}
	}
}

int main(int argc, char *argv[]) {
	char *line;

	srand(time(NULL));
	masterState = new MasterState();

	printf("Congratulations!\n\n");
	printf("You are the proud CEO of a brand new company: %s\n\n", masterState->getPlayerCompany()->getName());
	printf("You must make the best software (and the most money) using what you have been given.\n\n");

	linenoiseSetCompletionCallback(completion);
	linenoiseHistoryLoad("history.txt");

	// Advance time by 10 days just so something interesting might happen.
	masterState->advanceTime(10);

	while((line = linenoise("command> ")) != NULL) {
		if (line[0] != '\0') {
			int found = 0;
			for (int i = 0; i < num_commands; i++) {
				struct command currentCommand = commands[i];
				if (strncmp(currentCommand.shortName, line, strlen(currentCommand.shortName)) == 0) {
					currentCommand.callback(masterState, line);
					found = 1;
				}
			}
			if (found == 0) {
				printf("echo: '%s'\n", line);
			}
			linenoiseHistoryAdd(line);
			linenoiseHistorySave("history.txt");
		}
		free(line);

		int moneyLeft = masterState->getPlayerCompany()->getMoney();
		printf("You have %d money left\n", moneyLeft);
		if (moneyLeft <= 0) {
			printf("You have lost.\n");
			return 0;
		}
	}
	return 0;
}

void help_function(MasterState *masterState, const char *line) {
	for (int i = 0; i < num_commands; i++) {
		struct command currentCommand = commands[i];
		printf("%s\n", currentCommand.shortName);
		printf("\t%s\n", currentCommand.fullDesc);
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

		vector <Person *> *allPeople = masterState->getKnownPeople();
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
			return;
		}
	}

	printf("Who do you wish to hire?\n");
	people_function(masterState, "people");
	free(tmp);
}

void hire_autocomplete(MasterState *masterState, linenoiseCompletions *lc, const char *) {

}

void quit_function(MasterState *masterState, const char *line) {
	exit(0);
}

void people_function(MasterState *masterState, const char *line) {
	int index = 0;

	vector<Person *> *allPeople = masterState->getKnownPeople();

	for (vector<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		++index;
		Person *currentPerson = *it;
		cout << index << ": " << currentPerson->getFirstName() << " " << currentPerson->getLastName();
		if (currentPerson->getCompany())
			printf(" (%s)", currentPerson->getCompany()->getName());
		printf("\n   %02d Greed      %02d Initiative", currentPerson->getGreed(), currentPerson->getInitiative());
		printf("\n   %02d Ambition   %02d Creativity", currentPerson->getAmbition(), currentPerson->getCreativity());
		printf("\n\n");
	}
}