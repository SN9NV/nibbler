#include <ncurses.h>
#include "Snake.hpp"

const unsigned	windowWidth = 128;
const unsigned	windowHeight = 64;

void	initGame();
void	exitGame();
void	gameLoop();

int main() {



	return 0;
}

void	initGame() {
	initscr();
	raw();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();
	curs_set(false);
}

void	exitGame() {
	endwin();
}

void	gameLoop() {
	Snake	snake(windowWidth, windowHeight);
}