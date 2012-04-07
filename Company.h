#ifndef COMPANY_H
#define COMPANY_H

#include <list>
using std::list;

class Person;

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
	protected:
	private:
		char *_name;
		int _money;
		list<Person *> *_employees;
};

#endif
