#include "NCurses.hpp"

NCurses::NCurses(unsigned windowHeight, unsigned windowWidth, Snake &snake) :
		_key(NCurses::Key::NONE),
		_snake(snake) {
	this->_height = windowHeight;
	this->_width = windowWidth;

	initscr();
	//raw();
	cbreak();
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();
	curs_set(false);
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

	if (static_cast<unsigned>(y) < this->_height || static_cast<unsigned>(x) < this->_width) {
		mvprintw(0, 0, "Window needs to be at least %d chars high and %d chars long", this->_height, this->_width);
		mvprintw(y - 1, x - 7, "%3d %3d", x, y);
	} else {
		this->_drawSnake();
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

void NCurses::_drawSnake() {
	auto pieces = this->_snake.getPieces();
	auto it = pieces.begin();

	chtype c = 0;

	switch(this->_snake.getDirection()) {
		case Snake::Direction::UP:
			c = ACS_TTEE;
			break;
		case Snake::Direction::LEFT:
			c = ACS_LTEE;
			break;
		case Snake::Direction::DOWN:
			c = ACS_BTEE;
			break;
		default:
			c = ACS_RTEE;
	}

	mvaddch((*it).y, (*it++).x, c);

	while (it != pieces.end()) {
		mvaddch((*it).y, (*it++).x, ACS_CKBOARD + (it - pieces.begin()));
	}
}