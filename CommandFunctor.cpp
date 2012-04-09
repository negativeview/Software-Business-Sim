#include "CommandFunctor.h"
#include "MasterState.h"

CommandFunctor::CommandFunctor(MasterState *masterState, string prefix) {
	this->_masterState = masterState;
	this->_prefix = prefix;
}

string CommandFunctor::getPrefix() {
	return this->_prefix;
}

void CommandFunctor::executeCommand(const char *command) {

}

CommandFunctor::~CommandFunctor() {
	
}