#ifndef NIBBLER_MAIN_DISPLAY_HPP
#define NIBBLER_MAIN_DISPLAY_HPP

#include "nibbler.hpp"
#include "Snake.hpp"
#include <queue>

class Display {
public:
	Display();
	virtual ~Display();

	enum	Key {
		NONE,
		SPACE,
		P,
		Q,
		X,
		DOWN,
		UP,
		LEFT,
		RIGHT,
		QUIT,
		ONE,
		TWO,
		THREE
	};

	typedef	std::queue<Display::Key>	KeyQueue;

	virtual void			draw() = 0;
	virtual Display::Key	getKey() = 0;

	Snake::Direction		getInstruction();
	//Display::KeyQueue		&getKeyBuff();

protected:
	Display::KeyQueue	_keyBuff;
	Env					_env;

	unsigned			_score();

private:
	Display(const Display &src) = delete;
	Display &operator=(const Display &rhs) = delete;
};

extern "C" {
Display		*createDisplay(Env &env);
void		destroyDisplay(Display *display);
}


#endif //NIBBLER_MAIN_DISPLAY_HPP