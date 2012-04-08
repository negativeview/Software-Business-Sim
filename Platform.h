#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
using std::string;

class Platform {
	public:
		Platform(string name);
		~Platform();

		string getName();
	protected:
	private:
		string _name;
};

#endif