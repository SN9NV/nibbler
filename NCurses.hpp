#ifndef NIBBLER_MAIN_NCURSES_HPP
#define NIBBLER_MAIN_NCURSES_HPP

#include "Display.hpp"
#include <ncurses.h>

class NCurses : public Display {
public:
	NCurses(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food);
	virtual ~NCurses();

	Snake::Direction	getDirection();
	void				draw(unsigned tick);
	Display::Key		getKey();

	enum Key {
		NONE	= 0,
		P		= 112,
		Q		= 113,
		X		= 120,
		DOWN	= 258,
		UP		= 259,
		LEFT	= 260,
		RIGHT	= 261
	};

private:
	NCurses() = delete;
	NCurses(const NCurses &src) = delete;
	NCurses &operator=(const NCurses &rhs) = delete;

	void			_drawSnake();
	void			_drawWalls();
	void			_drawFood();

	NCurses::Key	_key;
	Snake			&_snake;
	Food			&_food;
};


#endif //NIBBLER_MAIN_NCURSES_HPP
