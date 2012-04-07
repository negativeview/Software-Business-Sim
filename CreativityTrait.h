#ifndef CREATIVITY_TRAIT_H
#define CREATIVITY_TRAIT_H

#include "Trait.h"

class CreativityTrait : public Trait {
	public:
		CreativityTrait(int amount);
		~CreativityTrait();
	protected:
	private:
		int _amount;
};

#endif