#ifndef PERSON_H
#define PERSON_H

#include <string>
using std::string;

#include <list>
using std::list;

#include <map>
using std::map;

class Company;
class Language;
class Platform;
class Trait;

class Person {
	public:
		Person(string firstName, string lastName, int money);
		~Person();

		string getFirstName();
		string getLastName();
		void hire(Company *company);
		Company *getCompany();

		int getCurrentSalary();
		void setSalary(int amount);
		void addMoney(int money);
		bool acceptWages(int money);
		void setPlatformSkill(Platform *platform, int skill);
		void setLanguageSkill(Language *language, int skill);
		list<Trait *> *getRealTraits();
		list<Trait *> *getBelievedTraits();
		map<Platform *, int> *getPlatformSkills();
		map<Language *, int> *getLanguageSkills();
	protected:
	private:
		string _firstName;
		string _lastName;
		int _money;
		int _currentSalary;
		Company *_company;
		map<Platform *, int> *_platformSkills;
		map<Language *, int> *_languageSkills;

		list<Trait *> *_actualTraits;
		list<Trait *> *_believedTraits;
};

#endif
