#ifndef NIBBLER_MAIN_DISPLAY_HPP
#define NIBBLER_MAIN_DISPLAY_HPP


#include "Snake.hpp"

class Display {
public:
	Display() {};
	Display(const Display &src) = delete;
	Display &operator=(const Display &rhs) = delete;
	Display(unsigned windowHeight, unsigned windowWidth) : _height(windowHeight), _width(windowWidth) {};
	virtual ~Display() {};

	enum Key {
		NONE,
		P,
		Q,
		X,
		DOWN,
		UP,
		LEFT,
		RIGHT,
	};

	virtual void				draw(unsigned tick) = 0;
	virtual Snake::Direction	getDirection() = 0;
	virtual Display::Key		getKey() = 0;

protected:
	unsigned	_height;
	unsigned	_width;
};


#endif //NIBBLER_MAIN_DISPLAY_HPP
