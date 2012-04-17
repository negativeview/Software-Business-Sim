#include "Company.h"
#include "EmployeesCommand.h"
#include "MasterState.h"
#include "Person.h"

EmployeesCommand::EmployeesCommand(MasterState *masterState) : CommandFunctor(masterState, "employees", "Hire an employee to work in your business.") {
	
}

void EmployeesCommand::executeCommand(const char *line) {
	int n_choices = this->_masterState->getPlayerCompany()->getEmployees()->size();
    keypad(stdscr, TRUE);
	MENU *my_menu = this->setupMenu(this->_masterState->getPlayerCompany()->getEmployees());
	WINDOW *my_menu_win = this->setupWindow(my_menu, "Employees");
	refresh();

    int c;
    int done = 0;
	while(!done) {
		c = wgetch(my_menu_win);
		switch(c) {
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10:	// Enter key, select the user.
				{
					ITEM *currentItem = current_item(my_menu);
//					ret = (Person *)item_userptr(currentItem);
					done = 1;
				}
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