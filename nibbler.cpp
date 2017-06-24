#include "nibbler.hpp"
#include "Display.hpp"

Display		*getActiveDisplay(void *handle, Env & env);
void		destroyDisplay(void *handle, Display *display);
Display		*switchDisplay(Display *display, Env &env, Nibbler::switches &switches, Display::Key key);

Nibbler::Switches	Nibbler::setSwitches(int argc, char **argv) {
	Switches	switches;

	for (int i = 1; i < argc; i++) {
		if (!std::strcmp(argv[i], "-w")) {
			switches.window.width = static_cast<unsigned>(atoi(argv[++i]));
			if (!switches.window.width) {
				switches.window.width = Nibbler::DefaultWindow::width;
				i--;
			}
		} else if (!std::strcmp(argv[i], "-h")) {
			switches.window.height = static_cast<unsigned>(atoi(argv[++i]));
			if (!switches.window.height) {
				switches.window.height = Nibbler::DefaultWindow::height;
				i--;
			}
		} else if (!std::strcmp(argv[i], "--food-value")) {
			if (argc > i)
				switches.foodValue = static_cast<unsigned>(atoi(argv[++i]));
		} else if (!std::strcmp(argv[i], "--eat-self")) {
			switches.eatSelf = true;
			switches.warp = false;
		} else if (!std::strcmp(argv[i], "--warp")) {
			switches.eatSelf = false;
			switches.warp = true;
		} else if (!std::strcmp(argv[i], "--infinite-snake")) {
			switches.eatSelf = true;
			switches.warp = true;
		} else if (!std::strcmp(argv[i], "--lib") && argv[i + 1] != NULL) {
			if (std::strcmp(argv[i + 1] + std::strlen(argv[i + 1]) - 3, ".so") != 0) {
				std::cerr << "Require library with format [libname].so" << std::endl;
				exit(EXIT_FAILURE);
			}

			i++;
			Nibbler::loadSharedLibs(argv[i], switches.handles);
		} else if (!std::strcmp(argv[i], "--help")) {
			std::cout << argv[0] << "\n"
						<< "    --lib { libname.so }    1-3 libs required. Loads the libs to key 1-3\n"
						<< "    -w { INT }              Window width, default is 32\n"
						<< "    -h { INT }              Window height, default is 32\n"
						<< "    --food-value { INT }    Multiplier on food value\n"
						<< "    --eat-self              Game doesn't end if you eat yourself. Body just gets smaller\n"
						<< "    --warp                  Game doesn't end if you collide with a wall. You warp to the other side\n"
						<< "    --infinite-snake        Turns on both warp and eat-self, so the game never ends\n"
						<< "warp and eat-self are complimentary. Only one can be set. The last one is taken\n";

			exit(0);
		}
	}

	if (!switches.handles.size()) {
		Nibbler::loadSharedLibs(const_cast<char *>("libCurses.so"), switches.handles);
	}

	return switches;
};

void		Nibbler::loadSharedLibs(const char *filename, Nibbler::HandleVector &libHandles) {
	void *handle = dlopen(filename, RTLD_LAZY | RTLD_LOCAL);
	if (!handle) {
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	libHandles.push_back(handle);
}

void		Nibbler::gameLoop(Nibbler::Switches &switches) {
	std::random_device	rd;
	std::mt19937		gen(rd());
	UniformDistribution	randomHeight(1, switches.window.height - 1);
	UniformDistribution	randomWidth(1, switches.window.width - 1);

	Env	env = { switches, NULL, NULL, NULL };
	env.snake	= new Snake(env);
	env.food	= new Food(env.switches.foodValue, { randomWidth(gen), randomHeight(gen) }, -1);
	env.score	= new unsigned(0);
	Display		*display = getActiveDisplay(switches.handles[switches.libIndex], env);
	unsigned	tick = 0;
	bool 		paused = false;

	while (true) {
		Display::Key key = display->getKey();
		if (key == Display::Key::P) {
			paused = !paused;
		} else if (key == Display::Key::Q) {
			break;
		} else if (key == Display::Key::ONE || key == Display::Key::TWO || key == Display::Key::THREE) {
			display = switchDisplay(display, env, switches, key);
			paused = true;
		} else if (key >= Display::Key::DOWN && key <= Display::Key::RIGHT) {
			paused = false;
		}

		if (!paused) {
			if (!(tick % 8) || key == Display::Key::SPACE) {
				env.snake->setDirection(display->getInstruction());

				if (env.snake->update())
					break;

				if (env.snake->getHead() == env.food->pos) {
					env.snake->eatFood(env.food->value);
					*env.score += env.food->value;

					do {
						env.food->pos = { randomWidth(gen), randomHeight(gen) };
					} while (*env.snake == env.food->pos);
				}

				display->draw();
			}

			tick++;
		}

		std::this_thread::sleep_for(std::chrono::microseconds(16666));
	}

	unsigned score = display->score();

	destroyDisplay(switches.handles[switches.libIndex], display);

	std::cout << "Your score: " << score << std::endl;
}

Display		*getActiveDisplay(void *handle, Env & env) {
	Display                 *(*activeDisplay)(Env);

	activeDisplay = (Display *(*)(Env)) dlsym(handle, "createDisplay");
	if (!activeDisplay) {
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	return activeDisplay(env);
}

void		destroyDisplay(void *handle, Display *display) {
	void    (*activeDisplay)(Display*);

	activeDisplay = (void (*)(Display*)) dlsym(handle, "destroyDisplay");
	if (!activeDisplay) {
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	activeDisplay(display);
}

Display		*switchDisplay(Display *display, Env &env, Nibbler::switches &switches, Display::Key key) {
	unsigned	newOption;

	newOption = key - Display::Key::ONE;
	if (newOption == switches.libIndex || newOption >= switches.handles.size())
		return display;
	destroyDisplay(switches.handles[switches.libIndex], display);
	switches.libIndex = newOption;
	return getActiveDisplay(switches.handles[switches.libIndex], env);
}