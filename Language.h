#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>
using std::string;

#include "RequirementProviderConsumer.h"

class Language : public RequirementProviderConsumer {
	public:
		Language(string name);
		~Language();

		string getName();
	protected:
	private:
		string _name;
};

#endif