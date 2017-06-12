#include <iostream>
#include "NCurses.hpp"

NCurses::NCurses(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food) :
		_key(NCurses::Key::NONE),
		_snake(snake),
		_food(food) {
	this->_height = windowHeight;
	this->_width = windowWidth;

	initscr();
	//raw();
	cbreak();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();
	curs_set(false);

	start_color();
	init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
}

NCurses::~NCurses() {
	endwin();
}

Snake::Direction NCurses::getDirection() {
	switch (this->_key) {
		case NCurses::Key::UP:
			return Snake::Direction::UP;
		case NCurses::Key::LEFT:
			return Snake::Direction::LEFT;
		case NCurses::Key::DOWN:
			return Snake::Direction::DOWN;
		case NCurses::Key::RIGHT:
			return Snake::Direction::RIGHT;
		default:
			return Snake::Direction::NONE;
	}
}

void NCurses::draw(unsigned tick) {
	int x, y;

	getmaxyx(stdscr, y, x);
	clear();
	mvprintw(y - 1, 0, "%8d", tick);

	if (static_cast<unsigned>(y) < this->_height || static_cast<unsigned>(x) < this->_width * 2) {
		mvprintw(0, 0, "Window needs to be at least %d chars high and %d chars long", this->_height, this->_width * 2);
		mvprintw(y - 1, x - 7, "%3d %3d", x, y);
	} else {
		this->_drawWalls();
		this->_drawSnake();
		this->_drawFood();
	}

	refresh();
}

Display::Key NCurses::getKey() {
	switch(getch()) {
		case NCurses::Key::P:
			this->_key = NCurses::Key::P;
			return Display::Key::P;
		case NCurses::Key::Q:
			this->_key = NCurses::Key::Q;
			return Display::Key::Q;
		case NCurses::Key::X:
			this->_key = NCurses::Key::X;
			return Display::Key::X;
		case NCurses::Key::UP:
			this->_key = NCurses::Key::UP;
			return Display::Key::UP;
		case NCurses::Key::LEFT:
			this->_key = NCurses::Key::LEFT;
			return Display::Key::LEFT;
		case NCurses::Key::DOWN:
			this->_key = NCurses::Key::DOWN;
			return Display::Key::DOWN;
		case NCurses::Key::RIGHT:
			this->_key = NCurses::Key::RIGHT;
			return Display::Key::RIGHT;
		default:
			this->_key = NCurses::Key::NONE;
			return Display::Key::NONE;
	}
}

void	drawPixel(unsigned y, unsigned x, chtype print) {
	mvaddch(y, x * 2, print);
	mvaddch(y, x * 2 + 1, print);
}

void NCurses::_drawSnake() {
	auto pieces = this->_snake.getPieces();
	auto it = pieces.begin();

	attron(COLOR_PAIR(COLOR_RED));
	drawPixel(it->y, it->x, ACS_CKBOARD);
	attroff(COLOR_PAIR(COLOR_RED));
	it++;

	attron(COLOR_PAIR(COLOR_YELLOW));
	for (;it != pieces.end(); it++) {
		drawPixel(it->y, it->x, ACS_CKBOARD);
	}
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void NCurses::_drawWalls() {
	attron(COLOR_PAIR(COLOR_BLUE));
	for (unsigned i = 0; i <= this->_width; i++) {
		drawPixel(0, i, ACS_CKBOARD);
		drawPixel(this->_height, i, ACS_CKBOARD);
	}

	for (unsigned i = 0; i < this->_height; i++) {
		drawPixel(i, 0, ACS_CKBOARD);
		drawPixel(i, this->_width, ACS_CKBOARD);
	}
	attroff(COLOR_PAIR(COLOR_BLUE));
}

void NCurses::_drawFood() {
	attron(COLOR_PAIR(COLOR_MAGENTA));
	mvaddch(this->_food.pos.y, this->_food.pos.x * 2, 'O');
	mvaddch(this->_food.pos.y, this->_food.pos.x * 2 + 1, '~');
	attroff(COLOR_PAIR(COLOR_MAGENTA));
}