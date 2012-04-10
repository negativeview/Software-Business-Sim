#ifndef MASTER_STATE_H
#define MASTER_STATE_H

#include <list>
using std::list;

#include <string>
using std::string;

#include <vector>
using std::vector;

class CommandFunctor;
class Company;
class Language;
class Person;
class Platform;

class MasterState {
	public:
		MasterState();
		~MasterState();

		list<string> *advanceTime(int amount);
		Company *getPlayerCompany();

		vector<Platform *> *getPlatforms();
		vector<Language *> *getLanguages();
		vector<CommandFunctor *> *getCommands();
		void executeCommand(const char *command);
		int getTime();
	protected:
	private:
		Company *_playerCompany;
		list<Company *> *_allCompanies;
		list<Person *> *_allWorkers;
		int _time;

		vector<string> *_firstNames;
		vector<string> *_lastNames;
		vector<Platform *> *_allPlatforms;
		vector<Language *> *_allLanguages;
		vector<CommandFunctor *> *_allCommands;

		void _setupFirstNames();
		void _setupLastNames();
		void _setupCommands();
		void _setupPlatforms();
		void _setupLanguages();
		void _createWorkers(int count);
		string _getRandomName(vector<string> *nameList);
		void (*_next_handler_pointer)(MasterState *masterState, const char *line);
};

#endif