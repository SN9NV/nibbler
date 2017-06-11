#include "NCurses.hpp"

NCurses::NCurses(unsigned windowHeight, unsigned windowWidth) :
		_height(windowHeight),
		_width(windowWidth),
		_key(NCurses::Key::NONE) {
	initscr();
	raw();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();
	curs_set(false);
}

NCurses::~NCurses() {
	endwin();
}

Snake::Direction NCurses::getDirection() {
	switch (getch()) {
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

void NCurses::update() {
	switch(getch()) {
		case NCurses::Key::Q:
			this->_key = NCurses::Key::Q;
			break;
		case NCurses::Key::X:
			this->_key = NCurses::Key::X;
			break;
		case NCurses::Key::UP:
			this->_key = NCurses::Key::UP;
			break;
		case NCurses::Key::LEFT:
			this->_key = NCurses::Key::LEFT;
			break;
		case NCurses::Key::DOWN:
			this->_key = NCurses::Key::DOWN;
			break;
		case NCurses::Key::RIGHT:
			this->_key = NCurses::Key::RIGHT;
			break;
		default:
			this->_key = NCurses::Key::NONE;
	}
}