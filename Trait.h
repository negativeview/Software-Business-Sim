#ifndef TRAIT_H
#define TRAIT_H

#include <string>
using std::string;

class Trait {
	public:
		Trait(string name);
		~Trait();

		virtual int influenceOnSalaryRequirements();
	protected:
	private:
		string _name;
};

#endif