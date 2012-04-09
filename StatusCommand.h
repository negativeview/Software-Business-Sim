#ifndef STATUS_COMMAND_H
#define STATUS_COMMAND_H

#include "CommandFunctor.h"

class MasterState;

class StatusCommand: public CommandFunctor {
	public:
		StatusCommand(MasterState *masterState);
		~StatusCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif