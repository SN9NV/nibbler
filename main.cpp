#include <thread>
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <dlfcn.h>

#include "Snake.hpp"
#include "Display.hpp"

const unsigned	windowWidth = 32;
const unsigned	windowHeight = 32;

void    checkArgv(int argc, char **argv, std::vector<std::string> & libFiles, unsigned int & foodValue)
{
	for(int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--food-value") == 0)
			foodValue = (unsigned int)atoi(argv[++i]);
		else if (strcmp(argv[i], "--lib") == 0)
			libFiles.push_back(std::string(argv[++i]));
	}
	if (libFiles.empty())
		libFiles.push_back("libCurses.so");
}

void    loadSharedLibs(std::vector<std::string> & libFiles, std::vector<void *> & libHandles)
{
	for (std::vector<std::string>::iterator it = libFiles.begin(); it != libFiles.end(); ++it){
		std::size_t ext = (it)->find_last_of(".");
		if (strcmp((it)->substr(ext).c_str(), ".so") != 0){
			std::cerr << "Error: lib should have a .so extension" << std::endl;
			exit(EXIT_FAILURE);
		}
		void* dl_handle = dlopen((it)->c_str(), RTLD_LAZY | RTLD_LOCAL);
		if (!dl_handle){
			std::cerr << "Error: " << dlerror() << std::endl;
			exit(EXIT_FAILURE);
		}
		libHandles.push_back(dl_handle);
	}
}

Display *setActiveLib(void *handle, unsigned width, unsigned height, Snake* snake, Food* food)
{
	Display                 *(*activeLib)(unsigned, unsigned, Snake*, Food*);

	activeLib = (Display *(*)(unsigned, unsigned, Snake*, Food*)) dlsym(handle, "createDisplay");
	if (!activeLib){
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	return activeLib(height, width, snake, food);
}

void    destroyActiveLib(void *handle, Display *display)
{
	void                 (*activeLib)(Display*);

	activeLib = (void (*)(Display*)) dlsym(handle, "destroyDisplay");
	if (!activeLib){
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	activeLib(display);
}

Display *swicthDisplay(std::vector<void *> & libHandles, Display::Key key, Snake & snake, Food & food, int *option, Display *display)
{
	int     newOption = *option;

	if (key == Display::Key::ONE)
		newOption = 0;
	else if (key == Display::Key::TWO)
		newOption = 1;
	else if (key == Display::Key::THREE)
		newOption = 2;
	if (newOption == *option || newOption > libHandles.size() - 1)
		return display;
	destroyActiveLib(libHandles[*option], display);
	*option = newOption;
	return setActiveLib(libHandles[*option], windowWidth, windowHeight, &snake, &food);
}

void    gameLoop(std::vector<void *> & libHandles, Display *display, Snake & snake, Food  & food, int *option)
{
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
		else if (key == Display::Key::ONE || key == Display::Key::TWO || key == Display::Key::THREE)
			display = swicthDisplay(libHandles, key, snake, food, option, display);

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
}

int     main(int argc, char **argv) {
	std::vector<std::string>  libFiles;
	std::vector<void *>       libHandles;
	unsigned int            foodValue = 1;
	Display                 *display;
	int                     option = 0;

	checkArgv(argc, argv, libFiles, foodValue);
	std::cout << "lib files size: " << libFiles.size() << std::endl;
	std::cout << "food value: " << foodValue << std::endl;

	loadSharedLibs(libFiles, libHandles);
	std::cout << "lib handles: " << libHandles.size() << std::endl;

	Snake   snake(windowWidth, windowHeight);
	Food    food(foodValue, {5, 9}, -1);
	display = setActiveLib(libHandles[option], windowWidth, windowHeight, &snake, &food);

	gameLoop(libHandles, display, snake, food, &option);
	destroyActiveLib(libHandles[option], display);
	return 0;
}