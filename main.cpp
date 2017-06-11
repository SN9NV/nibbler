#include <thread>

#include "Snake.hpp"
#include "Display.hpp"
#include "NCurses.hpp"

const unsigned	windowWidth = 128;
const unsigned	windowHeight = 64;

int main() {
	Snake	snake(windowWidth, windowHeight);
	Display	*display = new NCurses(windowHeight, windowWidth);

	while (true) {
		snake.setDirection(display->getDirection());

		if (snake.update())
			break;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	delete display;

	return 0;
}