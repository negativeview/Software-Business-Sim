#include "CommandFunctor.h"
#include "Company.h"
#include "Language.h"
#include "MasterState.h"
#include "Person.h"

#include <stdlib.h>

CommandFunctor::CommandFunctor(MasterState *masterState, string prefix, string fullDesc) {
	this->_masterState = masterState;
	this->_prefix = prefix;
	this->_fullDesc = fullDesc;
}

string CommandFunctor::getPrefix() {
	return this->_prefix;
}

string CommandFunctor::getFullDesc() {
	return this->_fullDesc;
}

MENU *CommandFunctor::setupMenu(vector<NamedObject *> *people) {
    int n_choices = people->size();
    ITEM **my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    int i = 0;
    for (vector<NamedObject *>::iterator it = people->begin(); it != people->end(); ++it) {
    	NamedObject *p = *it;
    	my_items[i] = new_item(p->getTag(), p->getFullName());
    	set_item_userptr(my_items[i], p);
    	i++;
    }
    // Add the sigil.
    my_items[i] = new_item(NULL, NULL);

	MENU *my_menu = new_menu((ITEM **)my_items);

	return my_menu;
}

WINDOW *CommandFunctor::setupWindow(MENU *my_menu, const char *title) {
	WINDOW *my_menu_win = newwin(10, 40, 4, 4);
	keypad(my_menu_win, TRUE);

    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

    box(my_menu_win, 0, 0);
    mvwprintw(my_menu_win, 1, 2, title);
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);

	post_menu(my_menu);
	wrefresh(my_menu_win);

	return my_menu_win;
}

Language *CommandFunctor::languageChoiceMenu() {
	Language *ret = NULL;

	int n_choices = this->_masterState->getLanguages()->size();
    keypad(stdscr, TRUE);
	MENU *my_menu = this->setupMenu((vector<NamedObject *> *)(this->_masterState->getLanguages()));
	WINDOW *my_menu_win = this->setupWindow(my_menu, "Language");
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
					ret = (Language *)item_userptr(currentItem);
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

Platform *CommandFunctor::platformChoiceMenu() {
	Platform *ret = NULL;

	int n_choices = this->_masterState->getPlatforms()->size();
    keypad(stdscr, TRUE);
	MENU *my_menu = this->setupMenu((vector<NamedObject *> *)(this->_masterState->getPlatforms()));
	WINDOW *my_menu_win = this->setupWindow(my_menu, "Platform");
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
					ret = (Platform *)item_userptr(currentItem);
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

Market *CommandFunctor::marketChoiceMenu() {
	Market *ret = NULL;

	int n_choices = this->_masterState->getMarkets()->size();
    keypad(stdscr, TRUE);
	MENU *my_menu = this->setupMenu((vector<NamedObject *> *)(this->_masterState->getMarkets()));
	WINDOW *my_menu_win = this->setupWindow(my_menu, "Market");
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
					ret = (Market *)item_userptr(currentItem);
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

Person *CommandFunctor::personChoiceMenu(const char *title) {
	Person *ret = NULL;

	int n_choices = this->_masterState->getPlayerCompany()->getKnownPeople()->size();
    keypad(stdscr, TRUE);
	MENU *my_menu = this->setupMenu((vector<NamedObject *> *)(this->_masterState->getPlayerCompany()->getKnownPeople()));
	WINDOW *my_menu_win = this->setupWindow(my_menu, title);
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

void CommandFunctor::executeCommand(const char *command) {

}

CommandFunctor::~CommandFunctor() {
	
}