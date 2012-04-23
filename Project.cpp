#include "Project.h"

Project::Project(Company *company, Language *language, Platform *platform, Market *market) {
	this->_company = company;
	this->_platform = platform;
	this->_language = language;
	this->_percentDone = 0;
}

Project::~Project() {
	
}