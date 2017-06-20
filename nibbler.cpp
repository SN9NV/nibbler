#include "nibbler.hpp"
#include "Display.hpp"

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
		}
	}

	return switches;
};

void Nibbler::gameLoop(Nibbler::Switches &switches) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned> randomHeight(1, Nibbler::DefaultWindow::height - 1);
	std::uniform_int_distribution<unsigned> randomWidth(1, Nibbler::DefaultWindow::width - 1);

	Env	env = { switches, NULL, NULL, { Nibbler::DefaultWindow::height, Nibbler::DefaultWindow::width } };
	env.snake	= new Snake(env);
	env.food	= new Food(env.switches.foodValue, { randomWidth(gen), randomHeight(gen) }, -1);
	Display			*display = createDisplay(env);
	unsigned		tick = 0;
	bool 			paused = false;

	while (true) {
		Display::Key key = display->getKey();
		if (key == Display::Key::P)
			paused = !paused;
		else if (key == Display::Key::Q)
			break;

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

	destroyDisplay(display);
}