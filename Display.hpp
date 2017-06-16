#ifndef NIBBLER_MAIN_DISPLAY_HPP
#define NIBBLER_MAIN_DISPLAY_HPP

#include "Snake.hpp"
#include <queue>

class Display {
public:
	Display(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food);
	virtual ~Display();

	enum Key {
		NONE,
		SPACE,
		P,
		Q,
		X,
		DOWN,
		UP,
		LEFT,
		RIGHT,
		QUIT
	};

	virtual void				draw(unsigned tick) = 0;
	virtual Display::Key		getKey() = 0;

	Snake::Direction			getInstruction();
	std::queue<Display::Key>	&getKeyBuff();

protected:
	unsigned					_height;
	unsigned					_width;
	std::queue<Display::Key>	_keyBuff;

	Snake						&_snake;
	Food						&_food;

private:
	Display() = delete;
	Display(const Display &src) = delete;
	Display &operator=(const Display &rhs) = delete;
};

extern "C" {
	Display		*createDisplay(unsigned windowHeight, unsigned windowWidth, Snake *snake, Food *food);
	void		destroyDisplay(Display *display);
}


#endif //NIBBLER_MAIN_DISPLAY_HPP
