#ifndef NIBBLER_MAIN_SNAKE_HPP
#define NIBBLER_MAIN_SNAKE_HPP

#include <deque>

class Snake {
public:
	struct	Point {
		unsigned	x;
		unsigned	y;

		Point() {};
		Point(unsigned x, unsigned y) : x(x), y(y) {};

		bool operator==(const Snake::Point &p2) const {
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

	Snake(unsigned windowWidth, unsigned windowHeight);
	virtual ~Snake();

	bool							update();
	void							setDirection(Snake::Direction direction);
	const std::deque<Snake::Point>	&getPieces() const;
	const Snake::Point				&getHead() const;
	Snake::Direction				getDirection() const;
	void 							eatFood(unsigned food);

	bool	operator==(Snake::Point &point) const;

private:
	Snake() = delete;
	Snake(const Snake &src) = delete;
	Snake &operator=(const Snake &rhs) = delete;

	Snake::Point				_getNewHeadPos();

	std::deque<Snake::Point>	_pieces;
	Snake::Direction			_direction;
	unsigned					_foodLeft;
	Point						_window;
};

struct	Food {
	unsigned		value;
	Snake::Point	pos;
	int				life;

	Food(unsigned value, Snake::Point point, int life) : value(value), pos(point), life(life) {}
};

#endif //NIBBLER_MAIN_SNAKE_HPP
