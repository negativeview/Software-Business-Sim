#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
using std::string;

#include "RequirementProviderConsumer.h"

class Platform : public RequirementProviderConsumer {
	public:
		Platform(string name);
		~Platform();

		string getName();
	protected:
	private:
		string _name;
};

#endif