#ifndef REQUIREMENT_PROVIDER_CONSUMER_H
#define REQUIREMENT_PROVIDER_CONSUMER_H

#include "NamedObject.h"

#include <map>
using std::map;

#include <string>
using std::string;

class RequirementProviderConsumer : public NamedObject {
	public:
		RequirementProviderConsumer(const char *key, const char *name);
		~RequirementProviderConsumer();

		void addRequirement(string name, int amount);
		void addProvides(string name, int amount);

		map<string, int> *getRequires();
		map<string, int> *getProvides();
	protected:
	private:
		map<string, int> *_requires;
		map<string, int> *_provides;
};

#endif