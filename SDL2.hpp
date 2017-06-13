#ifndef NIBBLER_MAIN_SDL2_HPP
#define NIBBLER_MAIN_SDL2_HPP

#include "Display.hpp"
#include <SDL2.h>

const unsigned	SDL_PIXEL_MULTIPLIER = 8;

class SDL2 : public Display {
public:
	SDL2(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food);
	virtual ~SDL2();

	void				draw(unsigned tick);
	Display::Key		getKey();

	enum Key {
		NONE	= 0,
		P		= 112,
		Q		= 113,
		X		= 120,
		DOWN	= 258,
		UP		= 259,
		LEFT	= 260,
		RIGHT	= 261
	};

	struct Colour {
		unsigned char	R;
		unsigned char	G;
		unsigned char	B;
		unsigned char	A;
	};

	struct Colours {
		SDL2::Colour	WHITE = {0x00, 0x00, 0x00, 0xFF};
		SDL2::Colour	RED = {0xFF, 0x00, 0x00, 0xFF};
		SDL2::Colour	BLUE = {0x00, 0x00, 0xFF, 0xFF};
		SDL2::Colour	YELLOW = {0xFF, 0xFF, 0x00, 0xFF};
		SDL2::Colour	MAGENTA = {0x8B, 0x00, 0x8B, 0xFF};
	};

private:
	SDL2() = delete;
	SDL2(const SDL2 &src) = delete;
	SDL2 &operator=(const SDL2 &rhs) = delete;

	void			_drawSnake();
	void			_drawWalls();
	void			_drawFood();

	SDL_Window		*_window;
	SDL_Renderer	*_renderer;
};


#endif //NIBBLER_MAIN_SDL2_HPP
