#include "Snake.hpp"

Snake::Snake() {
	this->_pieces = {{4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}};
	this->_direction = Snake::Direction::RIGHT;
}

Snake::Snake(const Snake &src) {
	*this = src;
}

Snake::Snake(unsigned windowWidth, unsigned windowHeight) {
	unsigned w = windowWidth / 2;
	unsigned h = windowHeight / 2;

	for (unsigned i = 5; i; i--) {
		this->_pieces.push_back({w--, h});
	}

	this->_direction = Snake::Direction::RIGHT;
}

Snake::~Snake() {}

Snake& Snake::operator=(const Snake &rhs) {
	this->_pieces = rhs._pieces;
	this->_direction = rhs._direction;

	return *this;
}

void Snake::update() {
	// If food value is 0, delete last block
	if (this->_foodLeft)
		this->_foodLeft--;
	else
		this->_pieces.pop_back();

	// Generate new head block in the current direction
	this->_pieces.push_front(this->_getNewHeadPos());
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
	this->_direction = direction;
}