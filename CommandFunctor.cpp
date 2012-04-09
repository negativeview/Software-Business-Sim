#include "CommandFunctor.h"
#include "MasterState.h"

CommandFunctor::CommandFunctor(MasterState *masterState, string prefix, string fullDesc) {
	this->_masterState = masterState;
	this->_prefix = prefix;
	this->_fullDesc = fullDesc;
}

string CommandFunctor::getPrefix() {
	return this->_prefix;
}

string CommandFunctor::getFullDesc() {
	return this->_fullDesc;
}

void CommandFunctor::executeCommand(const char *command) {

}

CommandFunctor::~CommandFunctor() {
	
}