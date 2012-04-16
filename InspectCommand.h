#ifndef INSPECT_COMMAND_H
#define INSPECT_COMMAND_H

#include "CommandFunctor.h"

class MasterState;

class InspectCommand: public CommandFunctor {
	public:
		InspectCommand(MasterState *masterState);
		~InspectCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif