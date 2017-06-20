#include "nibbler.hpp"
#include "Display.hpp"

Display     *getActiveDisplay(void *handle, Env & env);
void        destroyDisplay(void *handle, Display *display);
Display     *switchDisplay(Display *display, Env & env, Nibbler::switches & switches, Display::Key key);

Nibbler::Switches	Nibbler::setSwitches(int argc, char **argv) {
	Switches	switches = { 1, false, false };

	for (int i = 1; i < argc; i++) {
		if (!std::strcmp(argv[i], "--food-value")) {
			if (argc > i)
				switches.foodValue = static_cast<unsigned>(atoi(argv[++i]));
		} else if (!std::strcmp(argv[i], "--eat-self")) {
			switches.eatSelf = true;
			switches.warp = false;
		} else if (!std::strcmp(argv[i], "--warp")) {
			switches.eatSelf = false;
			switches.warp = true;
		} else if (!std::strcmp(argv[i], "--help")) {
			std::cout << argv[0] << "\n"
			          << "    --food-value { INT }    Multiplier on food value\n"
			          << "    --eat-self              Game doesn't end if you eat yourself. Body just gets smaller\n"
			          << "    --warp                  Game doesn't end if you collide with a wall. You warp to the other side\n"
			          << "warp and eat-self are complimentary. Only one can be set. the last one is taken\n";

			exit(0);
		} else if (!std::strcmp(argv[i], "--lib") && argv[i + 1] != NULL){
			if (std::strcmp(argv[i + 1] + std::strlen(argv[i + 1]) - 3, ".so") != 0){
				std::cerr << "Require library with format [libname].so" << std::endl;
				exit(EXIT_FAILURE);
			}
			i += 1;
			Nibbler::loadSharedLibs(argv[i], switches.handles);
		}
	}
	if (!switches.handles.size())
		Nibbler::loadSharedLibs((char *)"libCurses.so", switches.handles);
	return switches;
};

void Nibbler::loadSharedLibs(char *filename, std::vector<void *> &libHandles) {
	void *handle = dlopen(filename, RTLD_LAZY | RTLD_LOCAL);
	if (!handle){
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	libHandles.push_back(handle);
}

void Nibbler::gameLoop(Nibbler::Switches &switches) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned> randomHeight(1, Nibbler::DefaultWindow::height - 1);
	std::uniform_int_distribution<unsigned> randomWidth(1, Nibbler::DefaultWindow::width - 1);

	Env	env = { switches, NULL, NULL, { Nibbler::DefaultWindow::height, Nibbler::DefaultWindow::width } };
	env.snake	= new Snake(env);
	env.food	= new Food(env.switches.foodValue, { randomWidth(gen), randomHeight(gen) }, -1);
	Display			*display = getActiveDisplay(switches.handles[switches.libIndex], env);
	unsigned		tick = 0;
	bool 			paused = false;

	while (true) {
		Display::Key key = display->getKey();
		if (key == Display::Key::P)
			paused = !paused;
		else if (key == Display::Key::Q)
			break;
		else if (key == Display::Key::ONE || key == Display::Key::TWO || key == Display::Key::THREE)
			display = switchDisplay(display, env, switches, key);
		if (!paused) {
			if (!(tick % 8) || key == Display::Key::SPACE) {
				env.snake->setDirection(display->getInstruction());

				if (env.snake->update())
					break;

				if (env.snake->getHead() == env.food->pos) {
					env.snake->eatFood(env.food->value);
					do {
						env.food->pos = { randomWidth(gen), randomHeight(gen) };
					} while (*env.snake == env.food->pos);
				}

				display->draw(tick);
			}

			tick++;
		}

		std::this_thread::sleep_for(std::chrono::microseconds(16666));
	}
	destroyDisplay(switches.handles[switches.libIndex], display);
}

Display     *getActiveDisplay(void *handle, Env & env){
	Display                 *(*activeDisplay)(Env);

	activeDisplay = (Display *(*)(Env)) dlsym(handle, "createDisplay");
	if (!activeDisplay){
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	return activeDisplay(env);
}

void        destroyDisplay(void *handle, Display *display){
	void    (*activeDisplay)(Display*);

	activeDisplay = (void (*)(Display*)) dlsym(handle, "destroyDisplay");
	if (!activeDisplay){
		std::cerr << "Error: " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	activeDisplay(display);
}

Display     *switchDisplay(Display *display, Env & env, Nibbler::switches & switches, Display::Key key){
	unsigned    newOption;

	if (key == Display::Key::ONE)
		newOption = 0;
	else
		newOption = (key == Display::Key::TWO) ? 1 : 2;
	if (newOption == switches.libIndex || newOption >= switches.handles.size())
		return display;
	destroyDisplay(switches.handles[switches.libIndex], display);
	switches.libIndex = newOption;
	return getActiveDisplay(switches.handles[switches.libIndex], env);
}