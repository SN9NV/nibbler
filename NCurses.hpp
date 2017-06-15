#ifndef NIBBLER_MAIN_NCURSES_HPP
#define NIBBLER_MAIN_NCURSES_HPP

#include "Display.hpp"
#include <ncurses.h>

class NCurses : public Display {
public:
	NCurses(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food);
	virtual ~NCurses();

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
		RIGHT	= 261,
		ONE     = 49,
		TWO     = 50,
		THREE   = 51
	};

private:
	NCurses() = delete;
	NCurses(const NCurses &src) = delete;
	NCurses &operator=(const NCurses &rhs) = delete;

	void			_drawSnake();
	void			_drawWalls();
	void			_drawFood();
};

extern "C" {
	Display		*createDisplay(unsigned windowHeight, unsigned windowWidth, Snake *snake, Food *food);
	void		destroyDisplay(Display *display);
}


#endif //NIBBLER_MAIN_NCURSES_HPP
