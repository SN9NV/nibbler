#include "SDL2.hpp"

SDL2::Colour SDL2::Colours::BLACK = { 0x00, 0x00, 0x00, 0xFF };
SDL2::Colour SDL2::Colours::RED = { 0xFF, 0x00, 0x00, 0xFF };
SDL2::Colour SDL2::Colours::BLUE = { 0x00, 0x00, 0xFF, 0xFF };
SDL2::Colour SDL2::Colours::YELLOW = { 0xFF, 0xFF, 0x00, 0xFF };
SDL2::Colour SDL2::Colours::MAGENTA = { 0x8B, 0x00, 0x8B, 0xFF };

SDL2::SDL2(Env &env) {
	this->_env = env;
	this->_env.switches.window.width *= SDL2::PIXEL_MULTIPLIER;
	this->_env.switches.window.height *= SDL2::PIXEL_MULTIPLIER;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		throw std::runtime_error("Could not init video");
	}

	this->_window = SDL_CreateWindow("Snek", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		this->_env.switches.window.width + SDL2::PIXEL_MULTIPLIER, this->_env.switches.window.height + SDL2::PIXEL_MULTIPLIER, SDL_WINDOW_SHOWN);

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

	this->_renderer = nullptr;
	this->_window = nullptr;
}

void SDL2::draw() {
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
				case SDLK_1:
					return Display::Key::ONE;
				case SDLK_2:
					return Display::Key::TWO;
				case SDLK_3:
					return Display::Key::THREE;
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

	SDL2::SDL_SetRenderDrawColor(SDL2::Colours::RED);
	SDL_Rect	head = createPixel(it->x, it->y);
	SDL_RenderFillRect(this->_renderer, &head);
	it++;

	for (unsigned i = 0; i < length; i++) {
		SDL2::SDL_SetRenderDrawColor(SDL2::Colours::YELLOW);
		body[i] = createPixel(it->x, it->y);
		it++;
	}
	SDL_RenderFillRects(this->_renderer, body, static_cast<int>(length));
}

void SDL2::_drawWalls() {
	SDL2::SDL_SetRenderDrawColor(SDL2::Colours::BLUE);
	SDL_RenderClear(this->_renderer);

	SDL2::SDL_SetRenderDrawColor(SDL2::Colours::BLACK);
	SDL_Rect	background = {SDL2::PIXEL_MULTIPLIER, SDL2::PIXEL_MULTIPLIER,
							  static_cast<int>(this->_env.switches.window.width - SDL2::PIXEL_MULTIPLIER),
							  static_cast<int>(this->_env.switches.window.height - SDL2::PIXEL_MULTIPLIER)};
	SDL_RenderFillRect(this->_renderer, &background);
}

void SDL2::_drawFood() {
	SDL2::SDL_SetRenderDrawColor(SDL2::Colours::MAGENTA);
	SDL_Rect	food = createPixel(this->_env.food->pos.x, this->_env.food->pos.y);
	SDL_RenderFillRect(this->_renderer, &food);
}

int SDL2::SDL_SetRenderDrawColor(struct SDL2::Colour colour) {
	return ::SDL_SetRenderDrawColor(this->_renderer, colour.R, colour.G, colour.B, colour.A);
}

Display		*createDisplay(Env &env) {
	Display *newDisplay = new SDL2(env);

	newDisplay->draw();
	return newDisplay;
}

void		destroyDisplay(Display *display) {
	if (display != nullptr)
		delete display;
}