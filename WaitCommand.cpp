#include "WaitCommand.h"
#include "MasterState.h"

#include <stdio.h>

#include <vector>
using std::vector;

WaitCommand::WaitCommand(MasterState *masterState) : CommandFunctor(masterState, "wait", "Move forward <n> days (default: 7)") {
	
}

void WaitCommand::executeCommand(const char *line) {
	this->_masterState->advanceTime(7);
}

WaitCommand::~WaitCommand() {
	
}