#ifndef COMPANY_H
#define COMPANY_H

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <map>
using std::map;

class Language;
class Person;
class Platform;

class Company {
	public:
		Company(const char *name, int money);
		~Company();

		const char *getName();
		void addEmployee(Person *person);
		list<Person *> *getEmployees();
		void payWages(int wages);
		void payOverhead(int overhead);
		int getOverheadCost();
		int getMoney();
		void doPayments(int time);
		vector<Person *> *getKnownPeople();
		void addKnownPerson(Person *person);
		void learnAboutEmployees();
		void advanceTime(int time);
		map<Platform *, int> *getPlatformSkills();
		map<Language *, int> *getLanguageSkills();
	protected:
		void recomputeCompanySkills();
	private:
		char *_name;
		int _money;
		list<Person *> *_employees;
		vector<Person *> *_knownPeople;
		map<Platform *, int> *_platformSkills;
		map<Language *, int> *_languageSkills;
};

#endif
