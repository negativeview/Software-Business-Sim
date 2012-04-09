#ifndef HIRE_COMMAND_FUNCTOR
#define HIRE_COMMAND_FUNCTOR

#include "CommandFunctor.h"

class MasterState;

class HireCommand: public CommandFunctor {
	public:
		HireCommand(MasterState *masterState);
		~HireCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif