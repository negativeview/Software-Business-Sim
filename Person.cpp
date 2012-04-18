#include "Company.h"
#include "Language.h"
#include "Person.h"
#include "Platform.h"
#include "Trait.h"

#include <stdlib.h>
#include <stdio.h>

Person::Person(string firstName, string lastName, int money) {
	this->_firstName = firstName;
	this->_lastName = lastName;
	this->_money = money;
	this->_company = NULL;
	this->_currentSalary = 0;

	this->_platformSkills = new map<Platform *, int>();
	this->_languageSkills = new map<Language *, int>();

	/**
	 * A person has two sets of traits: actual and believed.
	 *
	 * The actual traits are those that are used when we're calculating the
	 * work being done. A person high in actual creativity will invent new
	 * things or think outside the box.
	 *
	 * The believed traits are what the person believes to be true about
	 * themselves. These will almost always be inflated, but can actually
	 * be lower than reality. Believed traits are used to calculate how much
	 * the person wants to be paid, what projects the person wants to be
	 * involved with/run.
	 *
	 * The actual traits can be gleaned by the performance evaluations, etc.
	 *
	 * The believed traits can be somewhat gleaned by watching how the person
	 * acts. There is no screen that will give you these numbers.
	 *
	 * The meta game is all about figuring out who knows their shit, who's
	 * lying, and how to manage the differences between the two.
	 */
	this->_actualTraits   = new list<Trait *>();
	this->_believedTraits = new list<Trait *>();

	int ambitionTrait = rand() % 100;
	this->_actualTraits->push_back(new Trait("ambition", ambitionTrait));
	ambitionTrait += ((rand() % 20) - 5);
	if (ambitionTrait > 100)
		ambitionTrait = 100;
	this->_believedTraits->push_back(new Trait("ambition", ambitionTrait));

	int greedTrait = rand() % 100;
	this->_actualTraits->push_back(new Trait("greed", greedTrait));
	greedTrait += ((rand() % 20) - 5);
	if (greedTrait > 100)
		greedTrait = 100;
	this->_believedTraits->push_back(new Trait("greed", greedTrait));

	int initiativeTrait = rand() % 100;
	this->_actualTraits->push_back(new Trait("initiative", initiativeTrait));
	initiativeTrait += ((rand() % 20) - 5);
	if (initiativeTrait > 100)
		initiativeTrait = 100;
	this->_believedTraits->push_back(new Trait("initiative", initiativeTrait));

	int creativityTrait = rand() % 100;
	this->_actualTraits->push_back(new Trait("creativity", creativityTrait));
	creativityTrait += ((rand() % 20) - 5);
	if (creativityTrait > 100)
		creativityTrait = 100;
	this->_believedTraits->push_back(new Trait("creativity", creativityTrait));
}

Company *Person::getCompany() {
	return this->_company;
}

map<Platform *, int> *Person::getPlatformSkills() {
	return this->_platformSkills;
}

map<Language *, int> *Person::getLanguageSkills() {
	return this->_languageSkills;
}

void Person::hire(Company *company) {
	this->_company = company;
}

string Person::getFirstName() {
	return this->_firstName;
}

string Person::getLastName() {
	return this->_lastName;
}

void Person::setSalary(int amount) {
	this->_currentSalary = amount;
}

int Person::getCurrentSalary() {
	return this->_currentSalary;
}

/**
 * Will this person work for this amount of money? This is currently based
 * entirely on their traits. Currently only ambition matters. Greed eventually
 * will as well. Actually, there's a lot of things that I want to make matter
 * eventually. One big problem is that right now a person will accept a lower
 * paying job with no other benefit to them. I need to take into account
 * their current salary, and the reputation of the company that's offering
 * the money. I also plan on taking into account the amount of money that this
 * person has stockpiled. There's a lot left before I can do that though
 * (give the person bills, etc.).
 *
 * Basically, this is the simplest possible algorithm that seems to somewhat
 * work. But in reality, it's horribly broken.
 */
bool Person::acceptWages(int money) {
	int traitInfluence = 0;
	for (list<Trait *>::iterator it = this->_believedTraits->begin(); it != this->_believedTraits->end(); ++it) {
		traitInfluence += (*it)->influenceOnSalaryRequirements();
	}

	float randomInfluence = ((rand() % 100) / 100.0);

	if (money >= traitInfluence * randomInfluence)
		return true;
	return false;
}

void Person::setPlatformSkill(Platform *platform, int skill) {
	(*this->_platformSkills)[platform] = skill;
}

void Person::setLanguageSkill(Language *language, int skill) {
	(*this->_languageSkills)[language] = skill;
}

list<Trait *> *Person::getRealTraits() {
	return this->_actualTraits;
}

list <Trait *> *Person::getBelievedTraits() {
	return this->_believedTraits;
}

void Person::addMoney(int money) {
	this->_money += money;
}

Person::~Person() {
	list<Trait *>::iterator traitIterator;
	for (traitIterator = this->_believedTraits->begin(); traitIterator != this->_believedTraits->end(); ++traitIterator) {
		Trait *t = *traitIterator;
		delete t;
	}	
	delete this->_believedTraits;
	this->_believedTraits = NULL;

	for (traitIterator = this->_actualTraits->begin(); traitIterator != this->_actualTraits->end(); ++traitIterator) {
		Trait *t = *traitIterator;
		delete t;
	}
	delete this->_actualTraits;
	this->_actualTraits = NULL;
	delete this->_platformSkills;
	this->_platformSkills = NULL;
}
