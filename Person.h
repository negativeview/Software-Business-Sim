#ifndef PERSON_H
#define PERSON_H

class Company;

class Person {
	public:
		Person(const char *firstName, const char *lastName, int money);
		~Person();

		const char *getFirstName();
		const char *getLastName();
		void hire(Company *company);
		Company *getCompany();
	protected:
	private:
		char *_firstName;
		char *_lastName;
		int _money;
		Company *_company;
};

#endif
