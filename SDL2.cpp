#include "SDL2.hpp"

SDL2::SDL2(Nibbler::Env env) {
	this->_env = env;
	this->_env.window.width *= SDL2::PIXEL_MULTIPLIER;
	this->_env.window.height *= SDL2::PIXEL_MULTIPLIER;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		throw std::runtime_error("Could not init video");
	}

	this->_window = SDL_CreateWindow("Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		this->_env.window.width + SDL2::PIXEL_MULTIPLIER, this->_env.window.height + SDL2::PIXEL_MULTIPLIER, SDL_WINDOW_SHOWN);

	if (this->_window == nullptr) {
		throw std::runtime_error("Could not create SDL2 window");
	}

	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);

	if (this->_renderer == nullptr) {
		throw std::runtime_error("Could not create renderer");
	}
}

SDL2::~SDL2() {
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);

	SDL_Quit();
}

void SDL2::draw(unsigned tick) {
	(void)tick;
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
				case SDLK_SPACE:
					return Display::Key::SPACE;
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

	return Display::Key::NONE;
}

SDL_Rect	createPixel(unsigned x, unsigned y) {
	return {
		static_cast<int>(x * SDL2::PIXEL_MULTIPLIER),
		static_cast<int>(y * SDL2::PIXEL_MULTIPLIER),
		static_cast<int>(SDL2::PIXEL_MULTIPLIER),
		static_cast<int>(SDL2::PIXEL_MULTIPLIER)
	};
}

void SDL2::_drawSnake() {
	auto pieces = this->_env.snake->getPieces();
	auto it = pieces.begin();
	auto length = pieces.size() - 1;

	SDL_Rect	body[length];

	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::RED.R, SDL2::Colours::RED.G, SDL2::Colours::RED.B, SDL2::Colours::RED.A);
	SDL_Rect	head = createPixel(it->x, it->y);
	SDL_RenderFillRect(this->_renderer, &head);
	it++;

	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::YELLOW.R, SDL2::Colours::YELLOW.G, SDL2::Colours::YELLOW.B, SDL2::Colours::YELLOW.A);
	for (unsigned i = 0; i < length; i++) {
		body[i] = createPixel(it->x, it->y);
		it++;
	}
	SDL_RenderFillRects(this->_renderer, body, static_cast<int>(length));
}

void SDL2::_drawWalls() {
	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::BLUE.R, SDL2::Colours::BLUE.G, SDL2::Colours::BLUE.B, SDL2::Colours::BLUE.A);
	SDL_RenderClear(this->_renderer);

	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::WHITE.R, SDL2::Colours::WHITE.G, SDL2::Colours::WHITE.B, SDL2::Colours::WHITE.A);
	SDL_Rect	background = {SDL2::PIXEL_MULTIPLIER, SDL2::PIXEL_MULTIPLIER,
							  static_cast<int>(this->_env.window.width - SDL2::PIXEL_MULTIPLIER),
							  static_cast<int>(this->_env.window.height - SDL2::PIXEL_MULTIPLIER)};
	SDL_RenderFillRect(this->_renderer, &background);
}

void SDL2::_drawFood() {
	SDL_SetRenderDrawColor(this->_renderer, SDL2::Colours::MAGENTA.R, SDL2::Colours::MAGENTA.G, SDL2::Colours::MAGENTA.B, SDL2::Colours::MAGENTA.A);
	SDL_Rect	food = createPixel(this->_env.food->pos.x, this->_env.food->pos.y);
	SDL_RenderFillRect(this->_renderer, &food);
}

Display		*createDisplay(Nibbler::Env &env) {
	return new SDL2(env);
}

void		destroyDisplay(Display *display) {
	if (display != nullptr)
		delete display;
}
