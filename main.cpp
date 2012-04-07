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
};
int num_commands = 3;

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

void quit_function(MasterState *masterState, const char *line) {
	exit(0);
}

void people_function(MasterState *masterState, const char *line) {
	int index = 0;

	list<Person *> *allPeople = masterState->getKnownPeople();

	for (list<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		++index;
		Person *currentPerson = *it;
		cout << index << ": " << currentPerson->getFirstName() << " " << currentPerson->getLastName();
		if (currentPerson->getCompany())
			printf(" (%s)", currentPerson->getCompany()->getName());
		printf("\n");
	}
}