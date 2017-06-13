#include "SDL2.hpp"

SDL2::SDL2(unsigned windowHeight, unsigned windowWidth, Snake &snake, Food &food) :
		Display(windowHeight, windowWidth, snake, food) {
	if (SDL_INIT(SDL_INIT_VIDEO)) {
		throw std::exception("Could not init video");
	}

	this->_window = SDL_CreateWindow("Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth * SDL_PIXEL_MULTIPLIER, windowHeight * SDL_PIXEL_MULTIPLIER, SDL_WINDOW_SHOWN);

	if (this->_window == nullptr) {
		throw std::exception("Could not create SDL2 window");
	}

	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);

	if (this->_renderer == nullptr) {
		throw std::exception("Could not create renderer");
	}
}

SDL2::~SDL2() {
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);

	SDL_Quit();
}

void SDL2::draw(unsigned tick) {
	this->_drawWalls(); //No clear because drawWalls clears the screen
	this->_drawSnake();
	this->_drawFood();

	SDL_RenderPresent(this->_renderer);
}

Display::Key SDL2::getKey() {
	SDL_Event	event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return Display::Key::QUIT;
		} else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch(event.key.keysym.sym) {
				case SDLK_p:
					return Display::Key::P;
				case SDLK_q:
					return Display::Key::Q;
				case SDLK_x:
					return Display::Key::X;
				case SDLK_UP:
					this->_keyBuff.push(Display::Key::UP);
					return Display::Key::UP;
				case SDLK_LEFT:
					this->_keyBuff.push(Display::Key::LEFT);
					return Display::Key::LEFT;
				case SDLK_DOWN:
					this->_keyBuff.push(Display::Key::DOWN);
					return Display::Key::DOWN;
				case SDLK_RIGHT:
					this->_keyBuff.push(Display::Key::RIGHT);
					return Display::Key::RIGHT;
				default:
					return Display::Key::NONE;
			}
		}
	}
}

SDL_Rect	createPixel(unsigned x, unsigned y) {
	x *= SDL_PIXEL_MULTIPLIER;
	y *= SDL_PIXEL_MULTIPLIER;

	return { x, y, x + SDL_PIXEL_MULTIPLIER, y + SDL_PIXEL_MULTIPLIER };
}

void SDL2::_drawSnake() {
	auto pieces = this->_snake.getPieces();
	auto it = pieces.begin();
	auto length = pieces.size() - 1;

	SDL_Rect	body[] = new SDL_Rect[length];

	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::RED);
	SDL_RenderFillRect(this->_renderer, createPixel(it->x, it->y));
	it++;

	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::YELLOW);
	unsigned i = 0;
	for (;it != pieces.end(); it++) {
		body[i++] = createPixel(it->x, it->y);
	}
	SDL_RenderFillRects(this->_renderer, body, length);
}

void SDL2::_drawWalls() {
	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::BLUE);
	SDL_RenderClear(this->_renderer);

	SDL_SetRenderDrawColor(this->_renderer, SDL::Colours::WHITE);
	SDL_RenderFillRect(SDL_PIXEL_MULTIPLIER, SDL_PIXEL_MULTIPLIER,
					this->_width - SDL_PIXEL_MULTIPLIER,
					this->_height - SDL_PIXEL_MULTIPLIER);
}

void SDL2::_drawFood() {
	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::MAGENTA);
	SDL_RenderFillRect(this->_renderer, createPixel(this->_food.x, this->_food.y));
}

Display		*createDisplay(unsigned windowHeight, unsigned windowWidth, Snake *snake, Food *food) {
	return new SDL2(windowHeight, windowWidth, *snake, *food);
}

void		destroyDisplay(Display *display) {
	if (display != nullptr)
		delete display;
}