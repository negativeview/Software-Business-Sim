#ifndef EMPLOYEES_COMMAND_FUNCTOR
#define EMPLOYEES_COMMAND_FUNCTOR

#include "CommandFunctor.h"

#include <menu.h>

class MasterState;

class EmployeesCommand: public CommandFunctor {
	public:
		EmployeesCommand(MasterState *masterState);
		~EmployeesCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif