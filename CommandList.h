#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

#include <vector>
using std::vector;

class CommandFunctor;
class MasterState;

class CommandList {
	public:
		CommandList(MasterState *ms);
		~CommandList();

		void executeCommand(const char *command);
	protected:
	private:
		vector<CommandFunctor *> *_commands;
};

#endif