#include "CommandFunctor.h"
#include "CommandList.h"
#include "EmployeesCommand.h"
#include "HireCommand.h"
#include "InterviewCommand.h"
#include "MasterState.h"
#include "PeopleCommand.h"
#include "ProjectCommand.h"
#include "QuitCommand.h"
#include "StatusCommand.h"
#include "WaitCommand.h"

#include <string.h>

CommandList::CommandList(MasterState *ms) {
	this->_commands = new vector<CommandFunctor *>();

	this->_commands->push_back(new EmployeesCommand(ms));
	this->_commands->push_back(new HireCommand(ms));
	this->_commands->push_back(new InterviewCommand(ms));
	this->_commands->push_back(new PeopleCommand(ms));
	this->_commands->push_back(new ProjectCommand(ms));
	this->_commands->push_back(new StatusCommand(ms));
	this->_commands->push_back(new WaitCommand(ms));
	this->_commands->push_back(new QuitCommand(ms));
}

void CommandList::executeCommand(const char *command) {
	if (command[0] != '\0') {
		int found = 0;
		for (vector<CommandFunctor *>::iterator it = this->_commands->begin(); it != this->_commands->end(); ++it) {
			CommandFunctor *commandFunctor = *it;
			string prefix = commandFunctor->getPrefix();

			if (strncmp(prefix.c_str(), command, strlen(prefix.c_str())) == 0) {
				commandFunctor->executeCommand(command);
				return;
			}
		}
	}
}

CommandList::~CommandList() {
	
}