#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>
using std::string;

class Language {
	public:
		Language(string name);
		~Language();

		string getName();
	protected:
	private:
		string _name;
};

#endif