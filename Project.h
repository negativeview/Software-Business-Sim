#ifndef PROJECT_H
#define PROJECT_H

class Company;
class Language;
class Market;
class Platform;

class Project {
	public:
		Project(Company *company, Language *language, Platform *platform, Market *market);
		~Project();
	protected:
	private:
		Company *_company;
		Platform *_platform;
		Language *_language;

		int _percentDone;
};

#endif