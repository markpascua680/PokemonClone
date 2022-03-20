#include <iostream>
#include "interface.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////	CLASS INTERFACE DEFINITIONS	////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Interface::Interface() {

	// End program if fail to initialize
	if (SDL_Init(SDL_INIT_EVERYTHING < 0)) {
		std::cout << "UNABLE TO SDL_INIT_EVERYTHING" << std::endl;
		EXIT_FAILURE;
	}

	// Create window
	_window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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

	SDL_FreeSurface(_surface);
}

Interface::~Interface() {

	SDL_DestroyWindow(_window);
}

// Takes rect of image, rect of destination on screen, and image file path
void Interface::render(SDL_Rect* clip, SDL_Rect* dstRect, std::string path) {

	SDL_Surface* image = IMG_Load(path.c_str());
	if (image == NULL)
		std::cout << "UNABLE TO OPEN IMAGE" << std::endl;

	// Then render image over background
	_texture = SDL_CreateTextureFromSurface(_renderer, image);
	SDL_RenderCopy(_renderer, _texture, clip, dstRect);

	SDL_DestroyTexture(_texture);
	SDL_FreeSurface(image);
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

// Saves a button's original image, image when it's hovered and the screen destination that it will be displayed at
void Interface::addButton(std::string button, SDL_Rect* srcRect, SDL_Rect* _hoverRect, SDL_Rect* dstRect, std::string filePath) {

	Button b = { *srcRect, *_hoverRect, *dstRect,  filePath };
	buttons[button] = b;
}

// Takes the name of the button
void Interface::displayButton(std::string button) {
	
	Button b = buttons[button];

	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	// Display the button's hover image if mouse is over it, display original image if not
	if (isButtonHovered(mousePos, button))
		render(&b.hoverRect, &b.dstRect, b.filePath);
	else
		render(&b.srcRect, &b.dstRect, b.filePath);
}

// Returns true if mouse is hovering over button
bool Interface::isButtonHovered(SDL_Point mousePos, std::string button) {

	Button b = buttons[button];
	if (SDL_PointInRect(&mousePos, &b.dstRect)) {
		return true;
	}

	return false;
}

// Saves the image's file path and rectangle
void Interface::addImage(std::string name, SDL_Rect* rect, std::string filePath) {

	Image i = { filePath, *rect };
	images[name] = i;
}

void Interface::displayImage(std::string name) {

	Image i = images[name];
	render(NULL, &i.rect, i.filepath);
}