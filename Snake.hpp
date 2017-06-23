#ifndef NIBBLER_MAIN_SNAKE_HPP
#define NIBBLER_MAIN_SNAKE_HPP

#include "nibbler.hpp"
#include <deque>

typedef struct env Env;

class Snake {
public:
	typedef	std::deque<Nibbler::Point>	body;

	enum	Direction {
		NONE,
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	Snake(Env &env);
	virtual ~Snake();

	bool					update();
	void					setDirection(Snake::Direction direction);
	const Snake::body		&getPieces() const;
	const Nibbler::Point	&getHead() const;
	Snake::Direction		getDirection() const;
	unsigned				size() const;
	void 					eatFood(unsigned food);

	bool	operator==(Nibbler::Point &point) const;

private:
	Snake() = delete;
	Snake(const Snake &src) = delete;
	Snake &operator=(const Snake &rhs) = delete;

	Nibbler::Point		_getNewHeadPos();

	Snake::body			_pieces;
	Snake::Direction	_direction;
	unsigned			_foodLeft;
	Env		&_env;
};

#endif //NIBBLER_MAIN_SNAKE_HPP
