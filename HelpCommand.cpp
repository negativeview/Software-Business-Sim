#include "HelpCommand.h"
#include "MasterState.h"

#include <stdio.h>

#include <vector>
using std::vector;

HelpCommand::HelpCommand(MasterState *masterState) : CommandFunctor(masterState, "help", "You're looking at it.") {
	
}

void HelpCommand::executeCommand(const char *line) {
	vector<CommandFunctor *> *commands = this->_masterState->getCommands();
	for (vector<CommandFunctor *>::iterator it = commands->begin(); it != commands->end(); ++it) {
		CommandFunctor *command = *it;
		printf("%s\n", command->getPrefix().c_str());
		printf("\t%s\n", command->getFullDesc().c_str());
	}
}

HelpCommand::~HelpCommand() {
	
}