#include "Snake.hpp"

Snake::Snake(Env &env) : _env(env) {
	this->_pieces.push_back({
		this->_env.window.width / 2,
		this->_env.window.height / 2
	});

	this->_direction = Snake::Direction::RIGHT;
	this->_foodLeft = 3;
}

Snake::~Snake() {}

bool Snake::update() {
	// If food value is 0, delete last block
	if (this->_foodLeft)
		this->_foodLeft--;
	else
		this->_pieces.pop_back();

	Nibbler::Point head = this->_getNewHeadPos();

	if (head.x == 0 || head.y == 0 || head.x == this->_env.window.width || head.y == this->_env.window.height) {
		if (this->_env.switches.warp) {
			if (head.x == 0)
				head.x = this->_env.window.width - 1;
			else if (head.y == 0)
				head.y = this->_env.window.height - 1;
			else if (head.x == this->_env.window.width)
				head.x = 1;
			else
				head.y = 1;
		} else {
			return true;
		}
	}

	for (unsigned i = 0; i < this->_pieces.size(); i++) {
		if (head == this->_pieces[i]) {
			if (this->_env.switches.eatSelf) {
				this->_pieces.resize(i);
			} else {
				return true;
			}
		}
	}

	// Generate new head block in the current direction
	this->_pieces.push_front(head);

	return false;
}

Nibbler::Point Snake::_getNewHeadPos() {
	Nibbler::Point	newHead = this->_pieces[0];

	switch (this->_direction) {
		case Snake::Direction::UP:
			newHead.y--;
			break;
		case Snake::Direction::DOWN:
			newHead.y++;
			break;
		case Snake::Direction::LEFT:
			newHead.x--;
			break;
		default: // Snake::Direction::RIGHT
			newHead.x++;
			break;
	}

	return newHead;
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

	if (direction != Snake::Direction::NONE && (this->_direction + direction) % 2)
		this->_direction = direction;
}

void Snake::eatFood(unsigned food){
	this->_foodLeft += food;
}

const Snake::body &Snake::getPieces() const {
	return this->_pieces;
}

const Nibbler::Point &Snake::getHead() const {
	return this->_pieces[0];
}

Snake::Direction Snake::getDirection() const {
	return this->_direction;
}

bool Snake::operator==(Nibbler::Point &point) const {
	for (auto &piece : this->_pieces) {
		if (point == piece)
			return true;
	}

	return false;
}