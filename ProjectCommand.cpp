#include "Company.h"
#include "Language.h"
#include "Platform.h"
#include "Project.h"
#include "ProjectCommand.h"
#include "MasterState.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
using std::vector;

#include <map>
using std::map;

ProjectCommand::ProjectCommand(MasterState *masterState) : CommandFunctor(masterState, "project", "Start a project.") {
	
}

void ProjectCommand::executeCommand(const char *line) {
	Language *language = this->languageChoiceMenu();
	if (language == NULL)
		return;

	Platform *platform = this->platformChoiceMenu();
	if (platform == NULL)
		return;

	Market *market = this->marketChoiceMenu();
	if (market == NULL)
		return;

	Project *project = new Project(this->_masterState->getPlayerCompany(), language, platform, market);
	this->_masterState->getPlayerCompany()->addProject(project);
}

ProjectCommand::~ProjectCommand() {
	
}