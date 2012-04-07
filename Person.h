#ifndef PERSON_H
#define PERSON_H

#include <string>
using std::string;

class Company;

class Person {
	public:
		Person(string firstName, string lastName, int money);
		~Person();

		string getFirstName();
		string getLastName();
		void hire(Company *company);
		Company *getCompany();
	protected:
	private:
		string _firstName;
		string _lastName;
		int _money;
		Company *_company;
};

#endif
