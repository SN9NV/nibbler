#ifndef NIBBLER_MAIN_NIBBLER_HPP
#define NIBBLER_MAIN_NIBBLER_HPP

#include <thread>
#include <random>
#include <iostream>
#include <cstring>

#include "Point.hpp"
#include "Snake.hpp"

class Snake;

namespace Nibbler {
	typedef struct	food {
		unsigned		value;
		Nibbler::Point	pos;
		int				life;

		food(unsigned value, Nibbler::Point point, int life) : value(value), pos(point), life(life) {}
	} Food;

	typedef struct defaultWindow {
		static constexpr unsigned	height = 32;
		static constexpr unsigned	width = 32;
	} DefaultWindow;

	typedef struct	window {
		unsigned	height;
		unsigned	width;
	} Window;

	typedef struct	switches {
		unsigned		foodValue;
		bool 			eatSelf;
		bool 			warp;
		Nibbler::Window	window;

		switches() {}
		switches(unsigned foodValue, bool eatSelf, bool warpThroughWalls, Nibbler::Window window) :
			foodValue(foodValue), eatSelf(eatSelf), warp(warpThroughWalls), window(window) {}
	} Switches;

	Nibbler::Switches	setSwitches(int argc, char **argv);
	void				gameLoop(Nibbler::Switches &switches);
};

typedef std::uniform_int_distribution<unsigned> randomDistribution;

typedef struct	env {
	Nibbler::Switches	switches;
	Snake				*snake;
	Nibbler::Food		*food;
	Nibbler::Window		window;
	unsigned			*score;
} Env;

#endif //NIBBLER_MAIN_NIBBLER_HPP