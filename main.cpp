#include "Company.h"
#include "MasterState.h"

#include <ncurses.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <vector>
using std::vector;

MasterState *masterState;

int main(int argc, char *argv[]) {
	int row, col;

	srand(time(NULL));
	masterState = new MasterState();

	masterState->addMessage("Congratulations!");
	masterState->addMessage("You are the proud CEO of a brand new company!");
	masterState->addMessage("You must make the best software (and the most money) using what you have been given.");

	// Advance time by 10 days just so something interesting might happen.
	masterState->advanceTime(10);

	int moneyLeft = masterState->getPlayerCompany()->getMoney();

	initscr();

	int currentDay = -1;
	while(true) {
		erase();
		getmaxyx(stdscr, row, col);

		// TODO: Fix this so that it goes to the far right.
		attron(A_STANDOUT);
		mvprintw(0, 0, " Day: %d Money: %d", masterState->getTime(), moneyLeft);
		for (int i = 27; i < col; ++i) {
			printw(" ");
		}
		attroff(A_STANDOUT);

		vector<char *> *messages = masterState->getMessages();
		for (int i = 0; i < messages->size(); ++i) {
			int thisRow = row - messages->size() - 2 + i;
			mvprintw(thisRow, 1, (*messages)[i]);
		}

		// Three blank spaces between options.

		move(2, col - 20);
		attron(A_STANDOUT);
		printw("      COMMANDS      ");
		attroff(A_STANDOUT);

		move(3, col - 20);
		attron(A_STANDOUT);
		printw(" A ");
		attroff(A_STANDOUT);

		char message[20];

		printw(" Applicants");
		sprintf(message, "[%d]", masterState->getPlayerCompany()->getKnownPeople()->size());
		move(3, col - strlen(message));
		printw(message);

		move(4, col - 20);
		attron(A_STANDOUT);
		printw(" I ");
		attroff(A_STANDOUT);
		printw(" Interview");

		move(5, col - 20);
		attron(A_STANDOUT);
		printw(" H ");
		attroff(A_STANDOUT);
		printw(" Hire");

		move(6, col - 20);
		attron(A_STANDOUT);
		printw(" E ");
		attroff(A_STANDOUT);
		printw(" *Employees");

		sprintf(message, "[%d]", masterState->getPlayerCompany()->getEmployees()->size());
		move(6, col - strlen(message));
		printw(message);

		move(7, col - 20);
		attron(A_STANDOUT);
		printw(" S ");
		attroff(A_STANDOUT);
		printw(" Status");

		move(8, col - 20);
		attron(A_STANDOUT);
		printw(" T ");
		attroff(A_STANDOUT);
		printw(" *Teams");

		move(9, col - 20);
		attron(A_STANDOUT);
		printw(" P ");
		attroff(A_STANDOUT);
		printw(" *Projects");
		sprintf(message, "[%d]", masterState->getPlayerCompany()->getProjects()->size());
		move(9, col - strlen(message));
		printw(message);

		move(10, col - 20);
		attron(A_STANDOUT);
		printw(" W ");
		attroff(A_STANDOUT);
		printw(" *Wait");

		move(11, col - 20);
		attron(A_STANDOUT);
		printw(" Q ");
		attroff(A_STANDOUT);
		printw(" Quit");

		refresh();
		curs_set(0);
		noecho();
		int input = getch();

		if (masterState->getTime() != currentDay) {
			masterState->clearMessages();
			currentDay = masterState->getTime();
		}
		switch(input) {
			case 'a':
				masterState->clearMessages();
				masterState->executeCommand("applicants");
				break;
			case 'e':
				masterState->clearMessages();
				masterState->executeCommand("employees");
				break;
			case 'h':
				masterState->executeCommand("hire");
				break;
			case 'i':
				masterState->executeCommand("interview");
				break;
			case 'p':
				masterState->executeCommand("project");
				break;
			case 's':
				masterState->clearMessages();
				masterState->executeCommand("status");
				break;
			case 'q':
				endwin();
				return 0;
			default:
				break;
		}
	}
	endwin();
	return 0;
}