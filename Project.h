#ifndef PROJECT_H
#define PROJECT_H

class Company;
class Language;
class Platform;

class Project {
	public:
		Project(Company *company, Platform *platform, Language *language);
		~Project();
	protected:
	private:
		Company *_company;
		Platform *_platform;
		Language *_language;

		int _percentDone;
};

#endif