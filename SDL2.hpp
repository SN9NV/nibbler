#ifndef NIBBLER_MAIN_SDL2_HPP
#define NIBBLER_MAIN_SDL2_HPP

#include <stdexcept>

#include "Display.hpp"
#include "SDL.h"

class SDL2 : public Display {
public:
	SDL2(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food);
	virtual ~SDL2();

	void				draw(unsigned tick);
	Display::Key		getKey();

	struct Colour {
		unsigned char	R;
		unsigned char	G;
		unsigned char	B;
		unsigned char	A;
	};

	typedef struct Colours {
		static constexpr SDL2::Colour	WHITE = {0x00, 0x00, 0x00, 0xFF};
		static constexpr SDL2::Colour	RED = {0xFF, 0x00, 0x00, 0xFF};
		static constexpr SDL2::Colour	BLUE = {0x00, 0x00, 0xFF, 0xFF};
		static constexpr SDL2::Colour	YELLOW = {0xFF, 0xFF, 0x00, 0xFF};
		static constexpr SDL2::Colour	MAGENTA = {0x8B, 0x00, 0x8B, 0xFF};
	} Colours;

	static constexpr unsigned PIXEL_MULTIPLIER = 16;

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
