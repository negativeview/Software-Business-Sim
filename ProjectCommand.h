#ifndef PROJECT_COMMAND_FUNCTOR
#define PROJECT_COMMAND_FUNCTOR

#include "CommandFunctor.h"

class MasterState;

class ProjectCommand: public CommandFunctor {
	public:
		ProjectCommand(MasterState *masterState);
		~ProjectCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif