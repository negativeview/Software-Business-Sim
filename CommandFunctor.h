#ifndef COMMAND_FUNCTOR_H
#define COMMAND_FUNCTOR_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <menu.h>

class Language;
class Market;
class MasterState;
class NamedObject;
class Person;
class Platform;

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
		Language *languageChoiceMenu();
		Platform *platformChoiceMenu();
		Market *marketChoiceMenu();
		MENU *setupMenu(vector<NamedObject *> *namedObjects);
		WINDOW *setupWindow(MENU *my_menu, const char *title);
	private:
		string _prefix;
		string _fullDesc;
};

#endif