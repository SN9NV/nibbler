#include "Display.hpp"

Display::Display(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food) :
		_height(windowHeight),
		_width(windowWidth),
		_snake(snake),
		_food(food) {}

Display::~Display() {}

Snake::Direction Display::getInstruction() {
	if (this->_keyBuff.empty())
		return Snake::Direction::NONE;

	Snake::Direction	direction;

	switch (this->_keyBuff.front()) {
		case Display::Key::UP:		direction = Snake::Direction::UP;		break;
		case Display::Key::LEFT:	direction = Snake::Direction::LEFT;		break;
		case Display::Key::DOWN:	direction = Snake::Direction::DOWN;		break;
		case Display::Key::RIGHT:	direction = Snake::Direction::RIGHT;	break;
		default:					direction = Snake::Direction::NONE;
	}

	this->_keyBuff.pop();
	return direction;
}

std::queue<Display::Key> &Display::getKeyBuff() {
	return this->_keyBuff;
}