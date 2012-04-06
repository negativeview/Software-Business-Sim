#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linenoise.h"
#include "Company.h"
#include "Person.h"

#include <list>
using std::list;

struct command {
	const char *shortName;
	void (*callback)(const char *);
	const char *fullDesc;
	void (*furtherOptions)(linenoiseCompletions *lc, const char *);
};

void help_function(const char *);
void quit_function(const char *);
void people_function(const char *);
void hire_function(const char *);
void hire_people_function(linenoiseCompletions *lc, const char *);
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
		"Hire a person for your company.",
		hire_people_function
	}
};
int num_commands = 4;

void completion(const char *buf, linenoiseCompletions *lc) {
	for (int i = 0; i < num_commands; i++) {
		struct command currentCommand = commands[i];
		if (strncmp(buf, currentCommand.shortName, strlen(buf)) == 0) {
			linenoiseAddCompletion(lc, currentCommand.shortName);
		}

		if (currentCommand.furtherOptions != NULL) {
			currentCommand.furtherOptions(lc, buf);
		}
	}
}

list<Person *> *allPeople;
Company *myCompany;

int main(int argc, char *argv[]) {
	char *line;

	myCompany = new Company("McMaster Corporation", 100000);

	allPeople = createPeople();

	printf("Congratulations!\n\n");
	printf("You are the proud CEO of a brand new company: %s\n\n", myCompany->getName());
	printf("You must make the best software (and the most money) using what you have been given.\n\n");

	linenoiseSetCompletionCallback(completion);
	linenoiseHistoryLoad("history.txt");

	while((line = linenoise("command> ")) != NULL) {
		if (line[0] != '\0') {
			int found = 0;
			for (int i = 0; i < num_commands; i++) {
				struct command currentCommand = commands[i];
				if (strncmp(currentCommand.shortName, line, strlen(currentCommand.shortName)) == 0) {
					currentCommand.callback(line);
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

void help_function(const char *line) {
	for (int i = 0; i < num_commands; i++) {
		struct command currentCommand = commands[i];
		printf("%s\n", currentCommand.shortName);
		printf("\t%s\n", currentCommand.fullDesc);
	}
}

void quit_function(const char *line) {
	exit(0);
}

void people_function(const char *line) {
	int index = 0;
	for (list<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		++index;
		Person *currentPerson = *it;
		printf("%d: %s %s", index, currentPerson->getFirstName(), currentPerson->getLastName());
		if (currentPerson->getCompany())
			printf(" (%s)", currentPerson->getCompany()->getName());
		printf("\n");
	}
}

void hire_function(const char *line) {
	char *tmp = (char *)malloc(strlen(line) + 1);
	strcpy(tmp, line);

	char *hire = strtok(tmp, " ");
	if (strcmp(hire, "hire") != 0) {
		perror("Got into the hire function without a hire command.");
		exit(-1);
	}

	char *firstName = strtok(NULL, " ");
	char *lastName = strtok(NULL, " ");

	for (list<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		Person *p = *it;

		if (strcmp(p->getFirstName(), firstName) != 0)
			continue;
		if (strcmp(p->getLastName(), lastName) != 0)
			continue;

		p->hire(myCompany);
	}

	free(tmp);
}

void hire_people_function(linenoiseCompletions *lc, const char *line) {
	for (list<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
		Person *p = *it;
		char *command = (char *)malloc(
			5 +
			strlen(p->getFirstName()) +
			1 +
			strlen(p->getLastName()) +
			1
		);
		sprintf(command, "hire %s %s", p->getFirstName(), p->getLastName());
		linenoiseAddCompletion(lc, command);
	}
}

list <Person *> *createPeople() {
	list <Person *> *tmpPeople = new list<Person *>();
	tmpPeople->push_back(new Person("Daniel", "Grace", 100));
	tmpPeople->push_back(new Person("Mark", "Seeman", 1000));
	tmpPeople->push_back(new Person("Jeremy", "Pepper", 10000));
	tmpPeople->push_back(new Person("Brianna", "Gohde", 1000));

	return tmpPeople;
}
