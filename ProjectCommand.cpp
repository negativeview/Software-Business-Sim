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
	char *tmp = (char *)malloc(strlen(line) + 1);
	strcpy(tmp, line);

	Platform *selectedPlatform = NULL;
	Language *selectedLanguage = NULL;
	int platformInt;
	int languageInt;

	char *hire = strtok(tmp, " ");
	char *platform = strtok(NULL, " ");
	char *language = strtok(NULL, " ");

	vector<Platform *> *platforms = this->_masterState->getPlatforms();
	if (platform == NULL) {
		map<Platform *, int> *platformSkills = this->_masterState->getPlayerCompany()->getPlatformSkills();

		printf("Pick a target platform:\n");
		int index = 0;
		for (vector<Platform *>::iterator it = platforms->begin(); it != platforms->end(); ++it) {
			Platform *p = *it;
			++index;
			printf("\t%3d: %s [Company skill: %d]\n", index, p->getName().c_str(), (*platformSkills)[p]);
		}

		printf("Then execute `project <n>`\n");
		free(tmp);
		return;
	} else {
		platformInt = atoi(platform);
		if (platformInt == 0 || platformInt > platforms->size()) {
			printf("ERROR: Invalid platform number.\n");
			return;
		}

		selectedPlatform = (*platforms)[platformInt-1];
	}

	vector<Language *> *languages = this->_masterState->getLanguages();
	if (language == NULL) {
		map<Language *, int> *languageSkills = this->_masterState->getPlayerCompany()->getLanguageSkills();

		printf("Pick a target programming language:\n");
		int index = 0;
		for (vector<Language *>::iterator it = languages->begin(); it != languages->end(); ++it) {
			Language *l = *it;
			++index;
			printf("\t%3d: %s [Company skill: %d]\n", index, l->getName().c_str(), (*languageSkills)[l]);
		}

		printf("Then execute `project %d <n>`\n", platformInt);
		free(tmp);
		return;
	} else {
		languageInt = atoi(language);
		if (languageInt == 0 || languageInt > languages->size()) {
			printf("ERROR: Invalid language number.\n");
			return;
		}

		selectedLanguage = (*languages)[languageInt-1];
	}

	Project *p = new Project(this->_masterState->getPlayerCompany(), selectedPlatform, selectedLanguage);\
	this->_masterState->getPlayerCompany()->addProject(p);

	printf("Created a new project\n");
}

ProjectCommand::~ProjectCommand() {
	
}