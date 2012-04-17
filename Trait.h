#ifndef TRAIT_H
#define TRAIT_H

#include <string>
using std::string;

class Trait {
	public:
		Trait(string name, int amount);
		~Trait();

		virtual int influenceOnSalaryRequirements();
		string getDiscoveryModifiedText();
		bool discoverMore();
		string getName();
	protected:
		int _amount;
		string _name;
		int _discoveryLevel;
	private:
};

#endif