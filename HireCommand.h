#ifndef HIRE_COMMAND_FUNCTOR
#define HIRE_COMMAND_FUNCTOR

#include "CommandFunctor.h"

#include <menu.h>

class MasterState;

class HireCommand: public CommandFunctor {
	public:
		HireCommand(MasterState *masterState);
		~HireCommand();

		void executeCommand(const char *command);
	protected:
	private:
		int doGetWage(Person *p);
		Person *doHireMenu();
		MENU *setupMenu();
		WINDOW *setupWindow(MENU *my_menu);
};

#endif