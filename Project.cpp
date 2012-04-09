#include "Project.h"

Project::Project(Company *company, Platform *platform, Language *language) {
	this->_company = company;
	this->_platform = platform;
	this->_language = language;
	this->_percentDone = 0;
}

Project::~Project() {
	
}