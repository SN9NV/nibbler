#ifndef NIBBLER_MAIN_SNAKE_HPP
#define NIBBLER_MAIN_SNAKE_HPP

#include <deque>

class Snake {
public:
	struct Point {
		int	x;
		int	y;
	};

	enum	Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	Snake();
	Snake(const Snake &src);
	Snake(unsigned windowWidth, unsigned windowHeight);
	~Snake();

	Snake &operator=(const Snake &rhs);

	void					update();
	void					setDirection(Snake::Direction direction);
	std::deque::size_type	size();

private:
	std::deque<Point>	_pieces;
	Snake::Direction	_direction;
	unsigned			_foodLeft;

	Snake::Point		_getNewHeadPos();
};


#endif //NIBBLER_MAIN_SNAKE_HPP
