#ifndef AMBITION_TRAIT_H
#define AMBITION_TRAIT_H

#include "Trait.h"

class AmbitionTrait : public Trait {
	public:
		AmbitionTrait(int amount);
		~AmbitionTrait();

		int influenceOnSalaryRequirements();
	protected:
	private:
};

#endif