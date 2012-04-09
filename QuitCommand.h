#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "CommandFunctor.h"

#include <stdlib.h>

class MasterState;

class QuitCommand: public CommandFunctor {
	public:
		QuitCommand(MasterState *masterState);
		~QuitCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif