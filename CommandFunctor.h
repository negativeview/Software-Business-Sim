#ifndef COMMAND_FUNCTOR_H
#define COMMAND_FUNCTOR_H

#include <string>
using std::string;

#include <vector>
using std::vector;

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
		Person *personChoiceMenu(const char *title);
		MENU *setupMenu(vector<Person *> *people);
		WINDOW *setupWindow(MENU *my_menu, const char *title);
	private:
		string _prefix;
		string _fullDesc;
};

#endif