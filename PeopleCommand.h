#ifndef PEOPLE_COMMAND_FUNCTOR
#define PEOPLE_COMMAND_FUNCTOR

#include "CommandFunctor.h"

class MasterState;

class PeopleCommand: public CommandFunctor {
	public:
		PeopleCommand(MasterState *masterState);
		~PeopleCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif