#include "NameContainer.h"


#include <stdlib.h>

NameContainer::NameContainer() {
	this->_firstNames = new vector<const char *>();
	this->_lastNames = new vector<const char *>();

	this->_setupLastNames();
	this->_setupFirstNames();
}

const char *NameContainer::getFirstName() {
	int length = this->_firstNames->size();
	int element = rand() % length;

	return (*this->_firstNames)[element];
}

const char *NameContainer::getLastName() {
	int length = this->_lastNames->size();
	int element = rand() % length;

	return (*this->_lastNames)[element];
}

void NameContainer::_setupLastNames() {
	this->_lastNames->push_back("Amundson");
	this->_lastNames->push_back("Anderson");
	this->_lastNames->push_back("Anniston");
	this->_lastNames->push_back("Birthler");
	this->_lastNames->push_back("Bishop");
	this->_lastNames->push_back("Bremer");
	this->_lastNames->push_back("Cannon");
	this->_lastNames->push_back("Compton");
	this->_lastNames->push_back("Dorland");
	this->_lastNames->push_back("Esbensen");
	this->_lastNames->push_back("Frazier");
	this->_lastNames->push_back("Gemoets");
	this->_lastNames->push_back("Gloege");
	this->_lastNames->push_back("Gohde");
	this->_lastNames->push_back("Grace");
	this->_lastNames->push_back("Green");
	this->_lastNames->push_back("Hemmingway");
	this->_lastNames->push_back("Jones");
	this->_lastNames->push_back("Kamke");
	this->_lastNames->push_back("Koehl");
	this->_lastNames->push_back("Lamb");
	this->_lastNames->push_back("Mars");
	this->_lastNames->push_back("Mason");
	this->_lastNames->push_back("Miller");
	this->_lastNames->push_back("Myers");
	this->_lastNames->push_back("Olson");
	this->_lastNames->push_back("Pepper");
	this->_lastNames->push_back("Poeschl");
	this->_lastNames->push_back("Reed");
	this->_lastNames->push_back("Reynolds");
	this->_lastNames->push_back("Runyon");
	this->_lastNames->push_back("Schilken");
	this->_lastNames->push_back("Schneider");
	this->_lastNames->push_back("Seemann");
	this->_lastNames->push_back("Simula");
	this->_lastNames->push_back("Smith");
	this->_lastNames->push_back("Spradlin");
	this->_lastNames->push_back("Tava");
	this->_lastNames->push_back("Wade");
	this->_lastNames->push_back("Wolever");
	this->_lastNames->push_back("Wurm");
}

void NameContainer::_setupFirstNames() {
	this->_firstNames->push_back("Aaron");
	this->_firstNames->push_back("Albert");
	this->_firstNames->push_back("Alice");
	this->_firstNames->push_back("Amanda");
	this->_firstNames->push_back("Antoinette");
	this->_firstNames->push_back("Barbara");
	this->_firstNames->push_back("Ben");
	this->_firstNames->push_back("Brad");
	this->_firstNames->push_back("Breen");
	this->_firstNames->push_back("Brianna");
	this->_firstNames->push_back("Charles");
	this->_firstNames->push_back("Chelsea");
	this->_firstNames->push_back("Christopher");
	this->_firstNames->push_back("Dan");
	this->_firstNames->push_back("Daniel");
	this->_firstNames->push_back("Dave");
	this->_firstNames->push_back("David");
	this->_firstNames->push_back("Devin");
	this->_firstNames->push_back("Donald");
	this->_firstNames->push_back("Elizabeth");
	this->_firstNames->push_back("Erica");
	this->_firstNames->push_back("Eve");
	this->_firstNames->push_back("Gary");
	this->_firstNames->push_back("Gillian");
	this->_firstNames->push_back("Gina");
	this->_firstNames->push_back("Greg");
	this->_firstNames->push_back("Hannah");
	this->_firstNames->push_back("James");
	this->_firstNames->push_back("Jamie");
	this->_firstNames->push_back("Jenna");
	this->_firstNames->push_back("Jennifer");
	this->_firstNames->push_back("Jeremy");
	this->_firstNames->push_back("John");
	this->_firstNames->push_back("Joseph");
	this->_firstNames->push_back("Julia");
	this->_firstNames->push_back("Linda");
	this->_firstNames->push_back("Lisa");
	this->_firstNames->push_back("Maria");
	this->_firstNames->push_back("Markus");
	this->_firstNames->push_back("Mark");
	this->_firstNames->push_back("Mary");
	this->_firstNames->push_back("Matt");
	this->_firstNames->push_back("Matthew");
	this->_firstNames->push_back("Michael");
	this->_firstNames->push_back("Patricia");
	this->_firstNames->push_back("Paul");
	this->_firstNames->push_back("Richard");
	this->_firstNames->push_back("Robert");
	this->_firstNames->push_back("Susan");
	this->_firstNames->push_back("Thomas");
	this->_firstNames->push_back("William");
}
