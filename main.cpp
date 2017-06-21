#include "nibbler.hpp"

int main(int argc, char *argv[]) {
	Nibbler::Switches	switches = Nibbler::setSwitches(argc, argv);
	Nibbler::gameLoop(switches);

	return 0;
}