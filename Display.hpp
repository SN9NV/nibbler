#ifndef NIBBLER_MAIN_DISPLAY_HPP
#define NIBBLER_MAIN_DISPLAY_HPP


#include "Snake.hpp"

class Display {
public:
	virtual Display(unsigned windowHeight, unsigned windowWidth) = 0;
	virtual ~Display() {};

	virtual void				update() = 0;
	virtual Snake::Direction	getDirection() = 0;

protected:
	Display() {};
	Display(const Display &src) {};
	Display &operator=(const Display &rhs) {};

	unsigned	_height;
	unsigned	_width;
};


#endif //NIBBLER_MAIN_DISPLAY_HPP
