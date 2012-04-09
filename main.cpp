#include "Company.h"
#include "MasterState.h"

#include "linenoise.h"

#include <stdlib.h>
#include <stdio.h>

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

	char *commandPrompt;
	asprintf(&commandPrompt, "day %d> ", masterState->getTime());
	while((line = linenoise(commandPrompt)) != NULL) {
		masterState->executeCommand(line);
		free(line);

		int moneyLeft = masterState->getPlayerCompany()->getMoney();
		printf("You have %d money left\n", moneyLeft);
		if (moneyLeft <= 0) {
			printf("You have lost.\n");
			delete masterState;
			return 0;
		}
		free(commandPrompt);
		asprintf(&commandPrompt, "day %d> ", masterState->getTime());
	}
	return 0;
}