#include "Company.h"
#include "EmployeesCommand.h"
#include "MasterState.h"
#include "Person.h"
#include "Trait.h"

EmployeesCommand::EmployeesCommand(MasterState *masterState) : CommandFunctor(masterState, "employees", "Hire an employee to work in your business.") {
	
}

void EmployeesCommand::executeCommand(const char *line) {
	int n_choices = this->_masterState->getPlayerCompany()->getEmployees()->size();
    keypad(stdscr, TRUE);
	MENU *my_menu = this->setupMenu((vector<NamedObject *> *)(this->_masterState->getPlayerCompany()->getEmployees()));
	WINDOW *my_menu_win = this->setupWindow(my_menu, "Employees");
	refresh();

	WINDOW *my_details_win = newwin(10, 30, 4, 44);
    box(my_details_win, 0, 0);
    mvwprintw(my_details_win, 1, 2, "Details");
	mvwaddch(my_details_win, 2, 0, ACS_LTEE);
	mvwhline(my_details_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_details_win, 2, 39, ACS_RTEE);

    int c;
    int done = 0;
	while(!done) {
		ITEM *currentItem = current_item(my_menu);
		if (currentItem) {
			Person *p = (Person *)item_userptr(currentItem);

			list<Trait *> *realTraits = p->getRealTraits();
			int down = 3;
			for(list<Trait *>::iterator it = realTraits->begin(); it != realTraits->end(); ++it) {
				Trait *t = *it;
				char message[30];
				sprintf(message, "%10s: %s", t->getName().c_str(), t->getDiscoveryModifiedText().c_str());
				wmove(my_details_win, down, 2);
				down++;
				wprintw(my_details_win, message);
			}
		}
		wrefresh(my_details_win);

		c = wgetch(my_menu_win);
		switch(c) {
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 27:
				done = 1;
				break;
		}

		wrefresh(my_menu_win);
	}

	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);

	ITEM **my_items = menu_items(my_menu);
	for(int i = 0; i < n_choices; ++i)
		free_item(my_items[i]);
	endwin();
	free_menu(my_menu);
}

EmployeesCommand::~EmployeesCommand() {
	
}