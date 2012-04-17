#ifndef COMMAND_FUNCTOR_H
#define COMMAND_FUNCTOR_H

#include <string>
using std::string;

#include <menu.h>

class MasterState;
class Person;

class CommandFunctor {
	public:
		CommandFunctor(MasterState *masterState, string prefix, string fullDesc);
		~CommandFunctor();

		string getPrefix();
		string getFullDesc();
		virtual void executeCommand(const char *command);
	protected:
		MasterState *_masterState;
		Person *personChoiceMenu();
		MENU *setupMenu();
		WINDOW *setupWindow(MENU *my_menu);
	private:
		string _prefix;
		string _fullDesc;
};

#endif