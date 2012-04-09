#ifndef HELP_COMMAND_FUNCTOR
#define HELP_COMMAND_FUNCTOR

#include "CommandFunctor.h"

class MasterState;

class HelpCommand: public CommandFunctor {
	public:
		HelpCommand(MasterState *masterState);
		~HelpCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif