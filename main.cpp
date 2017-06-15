#include <thread>
#include <random>
#include <iostream>
#include <list>
#include <string>

#include "Snake.hpp"
#include "Display.hpp"

const unsigned	windowWidth = 32;
const unsigned	windowHeight = 32;

void    checkArgv(int argc, char **argv, std::list<std::string> & libFiles, int & foodValue)
{
	for(int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--food-value") == 0)
			foodValue = atoi(argv[++i]);
		else if (strcmp(argv[i], "--lib") == 0)
			libFiles.push_back(std::string(argv[++i]));
	}
}

int     main(int argc, char **argv) {
	std::list<std::string>   libFiles;
	int                 foodValue = 1;

	checkArgv(argc, argv, libFiles, foodValue);
	std::cout << "lib files size: " << libFiles.size() << std::endl;
	std::cout << "food value: " << foodValue << std::endl;
	return 0;
}

/*int main(int argc, char **argv) {
	Snake			snake(windowWidth, windowHeight);
	Food			food((argc == 3 && !strcmp(argv[1], "--food-value")) ? static_cast<unsigned>(atoi(argv[2])) : 1, {5, 9}, -1);
	Display			*display = createDisplay(windowHeight, windowWidth, &snake, &food);
	unsigned		tick = 0;
	bool 			paused = false;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned> randomHeight(1, windowHeight - 1);
	std::uniform_int_distribution<unsigned> randomWidth(1, windowWidth - 1);

	while (true) {
		Display::Key key = display->getKey();
		if (key == Display::Key::P)
			paused = !paused;
		else if (key == Display::Key::Q)
			break;

		if (!paused) {
			if (!(tick % 8)) {
				snake.setDirection(display->getInstruction());

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

	destroyDisplay(display);

	return 0;
}*/