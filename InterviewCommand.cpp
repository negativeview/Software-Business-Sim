#include "InterviewCommand.h"
#include "MasterState.h"
#include "Person.h"
#include "Trait.h"

#include <stdlib.h>

InterviewCommand::InterviewCommand(MasterState *masterState) : CommandFunctor(masterState, "interview", "You're looking at it.") {
	
}

void InterviewCommand::executeCommand(const char *line) {
	while (true) {
		Person *toInterview = this->personChoiceMenu("Applicants");
		if (toInterview == NULL)
			return;

		bool learnedAnything = false;
		list<Trait *> *believedTraits = toInterview->getBelievedTraits();
		for (list<Trait *>::iterator it = believedTraits->begin(); it != believedTraits->end(); ++it) {
			Trait *t = *it;
			if (rand() % 2 == 0) {
				if (t->discoverMore()) {
					learnedAnything = true;
					char message[100];
					sprintf(message, "Learned more about %s %s's %s", toInterview->getFirstName().c_str(), toInterview->getLastName().c_str(), t->getName().c_str());
					this->_masterState->addMessage(message);
				}
			}
		}

		if (!learnedAnything) {
			this->_masterState->addMessage("That was a thoroughly disappointing interview, in which you learned nothing.");
		}
		this->_masterState->advanceTime(1);

		return;
	}
}

InterviewCommand::~InterviewCommand() {	
}