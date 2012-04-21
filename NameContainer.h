#ifndef NAME_CONTAINER_H
#define NAME_CONTAINER_H

#include <vector>
using std::vector;

class NameContainer {
	public:
		NameContainer();
		~NameContainer();

		const char *getFirstName();
		const char *getLastName();
	protected:
		void _setupFirstNames();
		void _setupLastNames();
	private:
		vector<const char *> *_firstNames;
		vector<const char *> *_lastNames;
};

#endif