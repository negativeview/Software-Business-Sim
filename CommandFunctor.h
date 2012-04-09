#ifndef COMMAND_FUNCTOR_H
#define COMMAND_FUNCTOR_H

#include <string>
using std::string;

class MasterState;

class CommandFunctor {
	public:
		CommandFunctor(MasterState *masterState, string prefix);
		~CommandFunctor();

		string getPrefix();
		virtual void executeCommand(const char *command);
	protected:
		MasterState *_masterState;
	private:
		string _prefix;
};

#endif