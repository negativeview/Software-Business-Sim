#include "Company.h"
#include "MasterState.h"

#include "linenoise.h"

#include <ncurses.h>

#include <stdlib.h>
#include <stdio.h>

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

	while(true) {
		getmaxyx(stdscr, row, col);
		attron(A_STANDOUT);
		mvprintw(0, 0, " Money: %10d", moneyLeft);
		for (int i = 18; i < col; ++i) {
			printw(" ");
		}
		attroff(A_STANDOUT);

		vector<char *> *messages = masterState->getMessages();
		for (int i = 0; i < messages->size(); ++i) {
			int thisRow = row - messages->size() - 2 + i;
			mvprintw(thisRow, 1, (*messages)[i]);
		}

		move(row - 1, 1);
		attron(A_STANDOUT);
		printw("I");
		attroff(A_STANDOUT);
		printw(" Interview");

		move(row - 1, 21);
		attron(A_STANDOUT);
		printw("S");
		attroff(A_STANDOUT);
		printw(" Status");

		move(row - 1, 41);
		attron(A_STANDOUT);
		printw("A");
		attroff(A_STANDOUT);
		printw(" Applicants");

		move(row - 1, 61);
		attron(A_STANDOUT);
		printw("T");
		attroff(A_STANDOUT);
		printw(" Teams");

		move(row - 1, 81);
		attron(A_STANDOUT);
		printw("P");
		attroff(A_STANDOUT);
		printw(" Projects");

		move(row - 1, 101);
		attron(A_STANDOUT);
		printw("Q");
		attroff(A_STANDOUT);
		printw(" Quit");

		refresh();
		curs_set(0);
		noecho();
		int input = getch();

		masterState->clearMessages();
		switch(input) {
			case 's':
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