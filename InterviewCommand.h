#ifndef INTERVIEW_COMMAND_H
#define INTERVIEW_COMMAND_H

#include "CommandFunctor.h"

class MasterState;

class InterviewCommand: public CommandFunctor {
	public:
		InterviewCommand(MasterState *masterState);
		~InterviewCommand();

		void executeCommand(const char *command);
	protected:
	private:
};

#endif