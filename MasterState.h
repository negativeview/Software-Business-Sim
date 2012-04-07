#ifndef MASTER_STATE_H
#define MASTER_STATE_H

#include <list>
using std::list;

#include <string>
using std::string;

#include <vector>
using std::vector;

class Company;
class Person;

class MasterState {
	public:
		MasterState();
		~MasterState();

		list<string> *advanceTime(int amount);
		Company *getPlayerCompany();
		vector <Person *> *getKnownPeople();
	protected:
	private:
		Company *_playerCompany;
		list<Company *> *_allCompanies;
		list<Person *> *_allPeople;
		vector<Person *> *_knownPeople;
		int _time;

		vector<string> *_firstNames;
		vector<string> *_lastNames;

		void _setupFirstNames();
		void _setupLastNames();
		void _createPeople(int count);
		string _getRandomName(vector<string> *nameList);
};

#endif