#ifndef INITIATIVE_TRAIT_H
#define INITIATIVE_TRAIT_H

#include "Trait.h"

class InitiativeTrait : public Trait {
	public:
		InitiativeTrait(int amount);
		~InitiativeTrait();
	protected:
	private:
		int _amount;
};

#endif