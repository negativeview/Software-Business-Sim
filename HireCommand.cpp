#include "Company.h"
#include "HireCommand.h"
#include "MasterState.h"
#include "Person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>
using std::vector;

#include <form.h>

HireCommand::HireCommand(MasterState *masterState) : CommandFunctor(masterState, "hire", "Hire an employee to work in your business.") {
	
}

MENU *HireCommand::setupMenu() {
	vector<Person *> *allPeople = this->_masterState->getPlayerCompany()->getKnownPeople();
    int n_choices = allPeople->size();
    ITEM **my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    int i = 0;
    for (vector<Person *>::iterator it = allPeople->begin(); it != allPeople->end(); ++it) {
    	Person *p = *it;
    	my_items[i] = new_item(p->getFirstName().c_str(), p->getLastName().c_str());
    	set_item_userptr(my_items[i], p);
    	i++;
    }
    // Add the sigil.
    my_items[i] = new_item(NULL, NULL);

	MENU *my_menu = new_menu((ITEM **)my_items);

	return my_menu;
}

WINDOW *HireCommand::setupWindow(MENU *my_menu) {
	WINDOW *my_menu_win = newwin(10, 40, 4, 4);
	keypad(my_menu_win, TRUE);

    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

    box(my_menu_win, 0, 0);
    mvwprintw(my_menu_win, 1, 2, "Applicants");
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);

	post_menu(my_menu);
	wrefresh(my_menu_win);

	return my_menu_win;
}

Person *HireCommand::doHireMenu() {
	Person *ret = NULL;

	int n_choices = this->_masterState->getPlayerCompany()->getKnownPeople()->size();
    keypad(stdscr, TRUE);
	MENU *my_menu = this->setupMenu();
	WINDOW *my_menu_win = this->setupWindow(my_menu);
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
					ret = (Person *)item_userptr(currentItem);
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
	return ret;
}

int HireCommand::doGetWage(Person *p) {
	FIELD *field[2];
	FORM *my_form;

	field[0] = new_field(1, 10, 4, 35, 0, 0);
	field[1] = NULL;

	set_field_back(field[0], A_UNDERLINE);
	field_opts_off(field[0], O_AUTOSKIP);
	set_field_type(field[0], TYPE_INTEGER, 0, 1, 1000000);

	my_form = new_form(field);
	post_form(my_form);
	refresh();

	mvprintw(4, 10, "Offer Amount (per year):");
	refresh();

	int ch;
	while (true) {
		ch = getch();
		switch(ch) {
			case KEY_DOWN:
				form_driver(my_form, REQ_NEXT_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
//			case KEY_DEL:
//				form_driver(my_form, REQ_DEL_PREV);
//				break;
			case 10:
				{
					// Lame attempt to force the buffer to be filled out.
					form_driver(my_form, REQ_NEXT_FIELD);

					char *buffer = field_buffer(field[0], 0);
					return atoi(buffer);
				}
				break;
			default:
				form_driver(my_form, ch);
				break;
		}
	}

	return -1;
}

void HireCommand::executeCommand(const char *line) {
	while (true) {
		Person *toHire = this->doHireMenu();
		if (toHire == NULL)
			return;

		int hireAmount = this->doGetWage(toHire);
		if (hireAmount < 0)
			continue;

		char message[100];

		if (toHire->acceptWages(hireAmount)) {
			toHire->hire(this->_masterState->getPlayerCompany());
			toHire->setSalary(hireAmount);
			this->_masterState->getPlayerCompany()->addEmployee(toHire);
			sprintf(message, "%s %s joined your company for %d/year", toHire->getFirstName().c_str(), toHire->getLastName().c_str(), hireAmount);
		} else {
			sprintf(message, "%s %s rejected your offer of %d/year", toHire->getFirstName().c_str(), toHire->getLastName().c_str(), hireAmount);
		}
		this->_masterState->addMessage(message);
		this->_masterState->advanceTime(1);
		return;
	}
}

HireCommand::~HireCommand() {
	
}