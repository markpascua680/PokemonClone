#include <iostream>
#include "interface.h"

Interface::Interface() {

	// End program if fail to initialize
	if (SDL_Init(SDL_INIT_EVERYTHING < 0)) {
		std::cout << "UNABLE TO SDL_INIT_EVERYTHING" << std::endl;
		EXIT_FAILURE;
	}

	// Create window
	_window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!_window) {
		std::cout << "UNABLE TO CREATE WINDOW" << std::endl;
		EXIT_FAILURE;
	}

	// Get window surface
	_surface = SDL_GetWindowSurface(_window);

	// Set surface color to white
	SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 255, 255, 255));

	// Create renderer
	_renderer = SDL_CreateRenderer(_window, -1, 0);

	// Fill the screen with color white
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);
	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
}

Interface::~Interface() {

	SDL_DestroyWindow(_window);
}

// Takes in images to render
void Interface::render(SDL_Rect* clip, SDL_Rect* dstRect, std::string path) {

	SDL_Surface* image = IMG_Load(path.c_str());
	if (image == NULL)
		std::cout << "UNABLE TO OPEN IMAGE" << std::endl;

	// Then render image over background
	_texture = SDL_CreateTextureFromSurface(_renderer, image);
	SDL_RenderCopy(_renderer, _texture, clip, dstRect);
}

// Clear Renderer
void Interface::clear() {

	SDL_RenderClear(_renderer);
}

// Updates screen
void Interface::update() {

	// Display rendered images
	SDL_RenderPresent(_renderer);

}

void Interface::setWindowWidth(int w) {

	this->WINDOW_WIDTH = w;
}
void Interface::setWindowHeight(int h) {
	
	this->WINDOW_HEIGHT = h;
}