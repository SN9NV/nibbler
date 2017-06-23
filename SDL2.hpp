#ifndef NIBBLER_MAIN_SDL2_HPP
#define NIBBLER_MAIN_SDL2_HPP

#include <stdexcept>

#include "nibbler.hpp"
#include "Display.hpp"
#include "SDL.h"

class SDL2 : public Display {
public:
	SDL2(Env &env);
	virtual ~SDL2();

	void				draw();
	Display::Key		getKey();

	typedef struct Colour {
		unsigned char	R;
		unsigned char	G;
		unsigned char	B;
		unsigned char	A;
	} Colour;

	struct Colours {
		static SDL2::Colour	BLACK;
		static SDL2::Colour	RED;
		static SDL2::Colour	BLUE;
		static SDL2::Colour	YELLOW;
		static SDL2::Colour	MAGENTA;
	};

	int		SDL_SetRenderDrawColor(const SDL2::Colour colour);

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
