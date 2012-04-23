#include "RequirementProviderConsumer.h"

RequirementProviderConsumer::RequirementProviderConsumer(const char *key, const char *name) : NamedObject(key, name) {
	this->_requires = new map<string, int>();
	this->_provides = new map<string, int>();
}

void RequirementProviderConsumer::addRequirement(string requirementName, int amount) {
	(*this->_requires)[requirementName] += amount;
}

map<string, int> *RequirementProviderConsumer::getRequires() {
	return this->_requires;
}

void RequirementProviderConsumer::addProvides(string requirementName, int amount) {
	(*this->_provides)[requirementName] += amount;
}

map<string, int> *RequirementProviderConsumer::getProvides() {
	return this->_provides;
}

RequirementProviderConsumer::~RequirementProviderConsumer() {

}