#ifndef NIBBLER_MAIN_NCURSES_HPP
#define NIBBLER_MAIN_NCURSES_HPP

#include "Display.hpp"
#include <ncurses.h>

class NCurses : public Display {
public:
	NCurses(unsigned windowHeight, unsigned windowWidth);
	virtual ~NCurses();

	Snake::Direction	getDirection();
	void				update();

	static enum Key {
		NONE	= 0,
		Q		= 113,
		X		= 120,
		DOWN	= 258,
		UP		= 259,
		LEFT	= 260,
		RIGHT	= 261
	};

private:
	NCurses() {};
	NCurses(const NCurses &src) {};
	NCurses &operator=(const NCurses &rhs) {};

	NCurses::Key	_key;
};


#endif //NIBBLER_MAIN_NCURSES_HPP
