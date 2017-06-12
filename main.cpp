#include <thread>
#include <random>
#include <iostream>

#include "Snake.hpp"
#include "Display.hpp"
#include "NCurses.hpp"

const unsigned	windowWidth = 32;
const unsigned	windowHeight = 32;



int main() {
	Snake			snake(windowWidth, windowHeight);
	Food			food(1, {5, 9}, -1);
	Display			*display = new NCurses(windowHeight, windowWidth, snake, food);
	unsigned		tick = 0;
	bool 			paused = false;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned> randomHeight(1, windowHeight - 1);
	std::uniform_int_distribution<unsigned> randomWidth(1, windowWidth - 1);

	while (true) {
		/*Display::Key key = display->getKey();
		if (key == Display::Key::P)
			paused = !paused;
		else if (key == Display::Key::Q)
			break;

		snake.setDirection(display->getDirection());*/

		if (!paused) {
			if (!(tick % 8)) {
				Display::Key key = display->getKey();
				if (key == Display::Key::P)
					paused = !paused;
				else if (key == Display::Key::Q)
					break;

				snake.setDirection(display->getDirection());

				if (snake.update())
					break;

				if (snake.getHead() == food.pos) {
					snake.eatFood(food.value);
					food.pos = {randomWidth(gen), randomHeight(gen)};
				}

				display->draw(tick);
			}

			tick++;
		}

		std::this_thread::sleep_for(std::chrono::microseconds(16666));
	}

	delete display;

	return 0;
}