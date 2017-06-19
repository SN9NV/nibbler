#ifndef NIBBLER_MAIN_POINT_HPP
#define NIBBLER_MAIN_POINT_HPP

namespace Nibbler {
	class Point {
	public:
		unsigned	x;
		unsigned	y;

		Point();
		Point(unsigned x, unsigned y);
		Point(const Nibbler::Point &src);
		~Point();

		Nibbler::Point	&operator=(const Nibbler::Point &rhs);

		bool	operator==(const Nibbler::Point &p2) const;
	};
}

#endif //NIBBLER_MAIN_POINT_HPP
