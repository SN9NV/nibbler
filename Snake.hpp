#ifndef NIBBLER_MAIN_SNAKE_HPP
#define NIBBLER_MAIN_SNAKE_HPP

#include <deque>

class Snake {
public:
	struct Point {
		unsigned	x;
		unsigned	y;

		Point() {};
		Point(unsigned x, unsigned y) : x(x), y(y) {};

		bool operator==(Point &p2) {
			return (this->x == p2.x && this->y == p2.y);
		}
	};

	enum	Direction {
		NONE,
		UP,
		RIGHT,
		DOWN,
		LEFT
	};


	Snake(const Snake &src);
	Snake(unsigned windowWidth, unsigned windowHeight);
	~Snake();

	Snake &operator=(const Snake &rhs);

	bool					update();
	void					setDirection(Snake::Direction direction);
	std::deque::size_type	size();
	void 					setFood(unsigned food, bool inc = false);

private:
	Snake();

	std::deque<Point>	_pieces;
	Snake::Direction	_direction;
	unsigned			_foodLeft;
	Point				_window;

	Snake::Point		_getNewHeadPos();
};


#endif //NIBBLER_MAIN_SNAKE_HPP
