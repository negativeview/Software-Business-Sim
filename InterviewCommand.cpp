#include "InterviewCommand.h"
#include "MasterState.h"

InterviewCommand::InterviewCommand(MasterState *masterState) : CommandFunctor(masterState, "interview", "You're looking at it.") {
	
}

void InterviewCommand::executeCommand(const char *line) {
}

InterviewCommand::~InterviewCommand() {
	
}