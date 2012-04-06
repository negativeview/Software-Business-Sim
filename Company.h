#ifndef COMPANY_H
#define COMPANY_H

class Company {
	public:
		Company(const char *name, int money);
		~Company();

		const char *getName();
	protected:
	private:
		char *_name;
		int _money;
};

#endif
