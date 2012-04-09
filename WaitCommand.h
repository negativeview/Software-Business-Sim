#ifndef WAIT_COMMAND_FUNCTOR
#define WAIT_COMMAND_FUNCTOR

#include "CommandFunctor.h"

class MasterState;

class WaitCommand: public CommandFunctor {
	public:
		WaitCommand(MasterState *masterState);
		~WaitCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif