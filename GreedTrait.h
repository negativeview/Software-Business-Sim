#ifndef GREED_TRAIT_H
#define GREED_TRAIT_H

#include "Trait.h"

class GreedTrait : public Trait {
	public:
		GreedTrait(int amount);
		~GreedTrait();
	protected:
	private:
		int _amount;
};

#endif