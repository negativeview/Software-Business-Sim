#include "Company.h"
#include "HireCommand.h"
#include "MasterState.h"
#include "Person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
using std::vector;

#include <menu.h>

HireCommand::HireCommand(MasterState *masterState) : CommandFunctor(masterState, "hire", "Hire an employee to work in your business.") {
	
}

void HireCommand::executeCommand(const char *line) {
	ITEM **my_items;
	MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices;
    int c;

    vector<Person *> *allPeople = this->_masterState->getPlayerCompany()->getKnownPeople();

    keypad(stdscr, TRUE);
    n_choices = allPeople->size();

    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    int i = 0;
    for (vector<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
    	Person *p = *it;
    	my_items[i++] = new_item(p->getFirstName().c_str(), p->getLastName().c_str());
    }
    my_items[i] = new_item(NULL, NULL);

	my_menu = new_menu((ITEM **)my_items);

	my_menu_win = newwin(10, 40, 4, 4);
	keypad(my_menu_win, TRUE);

	/* Set main window and sub window */
        set_menu_win(my_menu, my_menu_win);
        set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

	/* Set menu mark to the string " * " */
        set_menu_mark(my_menu, " * ");

	/* Print a border around the main window and print a title */
        box(my_menu_win, 0, 0);
	//print_in_middle(my_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
	mvprintw(LINES - 2, 0, "F1 to exit");
	refresh();
        
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);

	while((c = wgetch(my_menu_win)) != KEY_F(1))
	{       switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
		}
                wrefresh(my_menu_win);
	}	

	/* Unpost and free all the memory taken up */
        unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return;

	char *tmp = (char *)malloc(strlen(line) + 1);
	strcpy(tmp, line);

	char *hire = strtok(tmp, " ");
	char *number = strtok(NULL, " ");
	char *salary = strtok(NULL, " ");

	if (number != NULL && salary != NULL) {
		int realNumber = atoi(number);
		int realSalary = atoi(salary);

		vector <Person *> *allPeople = this->_masterState->getPlayerCompany()->getKnownPeople();
		if (realNumber != 0 && salary != 0 && realNumber <= allPeople->size()) {
			Person *p = (*allPeople)[realNumber-1];
			if (p->acceptWages(realSalary)) {
				p->hire(this->_masterState->getPlayerCompany());
				this->_masterState->getPlayerCompany()->addEmployee(p);
				p->setSalary(realSalary);
			} else {
				printf("%s %s rejected your offer\n", p->getFirstName().c_str(), p->getLastName().c_str());
			}

			// Hiring people takes time.
			this->_masterState->advanceTime(1);
			free(tmp);
			return;
		}
	}
	free(tmp);
}

HireCommand::~HireCommand() {
	
}