#include "QuitCommand.h"
#include "MasterState.h"

#include <stdio.h>

#include <vector>
using std::vector;

QuitCommand::QuitCommand(MasterState *masterState) : CommandFunctor(masterState, "quit", "Quits the application.") {
	
}

void QuitCommand::executeCommand(const char *line) {
	exit(0);
}

QuitCommand::~QuitCommand() {
	
}