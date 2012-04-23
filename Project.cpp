#include "Project.h"

Project::Project(Company *company, Language *language, Platform *platform, Market *market) {
	this->_company = company;
	this->_platform = platform;
	this->_language = language;
	this->_market = market;
	this->_percentDone = 0;
}

Platform *Project::getPlatform() {
	return this->_platform;
}

Language *Project::getLanguage() {
	return this->_language;
}

Market *Project::getMarket() {
	return this->_market;
}

Project::~Project() {
	
}