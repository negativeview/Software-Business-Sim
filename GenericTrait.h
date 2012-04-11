#ifndef GENERIC_TRAIT_H
#define GENERIC_TRAIT_H

#include <string>
using std::string;

class GenericTrait {
	public:
		GenericTrait(string name);

		string getName();
		void addNewValue(int value);
		float getAverageSkill();
	protected:
	private:
		string _name;
		int _sum;
		int _count;
};

#endif