#include "Snake.hpp"

Snake::Snake() {}

Snake::Snake(const Snake &src) {
	*this = src;
}

Snake::Snake(unsigned windowWidth, unsigned windowHeight) : _window({windowHeight, windowWidth}) {
	unsigned w = windowWidth / 2;
	unsigned h = windowHeight / 2;

	for (unsigned i = 5; i; i--) {
		this->_pieces.push_back({w--, h});
	}

	this->_direction = Snake::Direction::RIGHT;
}

Snake::~Snake() {}

Snake& Snake::operator=(const Snake &rhs) {
	this->_window = rhs._window;
	this->_pieces = rhs._pieces;
	this->_foodLeft = rhs._foodLeft;
	this->_direction = rhs._direction;

	return *this;
}

bool Snake::update() {
	// If food value is 0, delete last block
	if (this->_foodLeft)
		this->_foodLeft--;
	else
		this->_pieces.pop_back();

	Snake::Point head = this->_getNewHeadPos();

	if (head.x == 0 || head.y == 0 || head.x == this->_window.x || head.y == this->_window.y)
		return true;

	for (auto &piece : this->_pieces) {
		if (head == piece)
			return true;
	}

	// Generate new head block in the current direction
	this->_pieces.push_front(head);

	return false;
}

Point Snake::_getNewHeadPos() {
	Point	newHead = this->_pieces[0];

	switch (this->_direction) {
		case Snake::Direction::UP:
			newHead.y--;
			return newHead;
		case Snake::Direction::DOWN:
			newHead.y++;
			return newHead;
		case Snake::Direction::LEFT:
			newHead.x--;
			return newHead;
		default: // Snake::Direction::RIGHT
			newHead.x++;
			return newHead;
	}
}

std::deque::size_type Snake::size() {
	return this->_pieces.size();
}

void Snake::setDirection(Snake::Direction direction) {
	/*
	 * NONE		= 0
	 * UP		= 1
	 * RIGHT	= 2
	 * DOWN		= 3
	 * LEFT		= 4
	 *
	 * UP + UP		= 1 + 1 = 2 ILLEGAL
	 * UP + RIGHT	= 1 + 2 = 3
	 * UP + DOWN	= 1 + 3 = 4 ILLEGAL
	 * UP + LEFT	= 1 + 4 = 5
	 *
	 * RIGHT + UP		= 2 + 1 = 3
	 * RIGHT + RIGHT	= 2 + 2 = 4 ILLEGAL
	 * RIGHT + DOWN		= 2 + 3 = 5
	 * RIGHT + LEFT		= 2 + 4 = 6 ILLEGAL
	 *
	 * Illegal moves % 2 == 0; so only change direction if new direction is odd
	 */

	if (direction != Snake::Direction::NONE && this->_direction + direction % 2)
		this->_direction = direction;
}

void Snake::setFood(unsigned food, bool inc) {
	this->_foodLeft = inc ? this->_foodLeft + food : food;
}