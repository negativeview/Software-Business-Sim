#ifndef MARKET_H
#define MARKET_H

#include "RequirementProviderConsumer.h"

class Market : public RequirementProviderConsumer {
	public:
		Market(const char *name);
		~Market();
	protected:
	private:
};

#endif