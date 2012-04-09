#include "Company.h"
#include "Platform.h"
#include "ProjectCommand.h"
#include "MasterState.h"

#include <stdio.h>

#include <vector>
using std::vector;

#include <map>
using std::map;

ProjectCommand::ProjectCommand(MasterState *masterState) : CommandFunctor(masterState, "project", "Start a project.") {
	
}

void ProjectCommand::executeCommand(const char *line) {
	vector<Platform *> *platforms = this->_masterState->getPlatforms();
	map<Platform *, int> *platformSkills = this->_masterState->getPlayerCompany()->getPlatformSkills();

	printf("Pick a target platform:\n");
	int index = 0;
	for (vector<Platform *>::iterator it = platforms->begin(); it != platforms->end(); ++it) {
		Platform *p = *it;
		++index;
		printf("\t%3d: %s [Company skill: %d]\n", index, p->getName().c_str(), (*platformSkills)[p]);
	}

	//masterState->setNextHandler(choose_target_platform);
}

ProjectCommand::~ProjectCommand() {
	
}