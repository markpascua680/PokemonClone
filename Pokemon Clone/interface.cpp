#include <iostream>
#include "interface.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////	CLASS BUTTON DEFINITIONS	////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Button::Button() {

}

Button::Button(SDL_Rect sRect, SDL_Rect hRect, SDL_Rect dRect, std::string path) :
	srcRect(sRect),
	hoverRect(hRect),
	dstRect(dRect),
	filePath(path)
{}

Button::~Button() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////	CLASS INTERFACE DEFINITIONS	   /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Interface::Interface() {

	_font = NULL;
	_fontSize = 0;

	// End program if fail to initialize
	if (SDL_Init(SDL_INIT_EVERYTHING < 0)) {
		std::cout << "UNABLE TO SDL_INIT_EVERYTHING" << std::endl;
		EXIT_FAILURE;
	}

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		std::cout << "UNABLE TO IMG_INIT" << std::endl;
		EXIT_FAILURE;
	}

	if (TTF_Init() < 0) {
		std::cout << "UNABLE TO TTF_INIT" << std::endl;
		EXIT_FAILURE;
	}

	// Create window
	_window = SDL_CreateWindow("Pokemon Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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

// Flips image
void Interface::renderFlip(SDL_Rect* clip, SDL_Rect* dstRect, std::string path, double angle, const SDL_Point* center, SDL_RendererFlip flip) {

	SDL_Surface* image = IMG_Load(path.c_str());
	if (image == NULL)
		std::cout << "UNABLE TO OPEN IMAGE" << std::endl;

	// Then render image over background
	_texture = SDL_CreateTextureFromSurface(_renderer, image);
	SDL_RenderCopyEx(_renderer, _texture, clip, dstRect, angle, center, flip);

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

	// Display the button's hover image if mouse is over it, display original image if not
	if (isButtonHovered(mousePos, b.dstRect))
		render(&b.hoverRect, &b.dstRect, b.filePath);
	else
		render(&b.srcRect, &b.dstRect, b.filePath);
}

// Returns true if mouse is hovering over button
bool Interface::isButtonHovered(SDL_Point mousePos, SDL_Rect rect) {

	if (SDL_PointInRect(&mousePos, &rect)) {
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

void Interface::setFont(std::string fontFile) {
	
	_font = TTF_OpenFont(fontFile.c_str(), _fontSize);

	if (!_font)
		std::cout << TTF_GetError() << std::endl;
}

void Interface::setFontSize(int size) {

	_fontSize = size;
}

void Interface::displayText(std::string text, SDL_Rect* dstRect, SDL_Color color) {

	_surface = TTF_RenderText_Solid(_font, text.c_str(), color);
	_texture = SDL_CreateTextureFromSurface(_renderer, _surface);

	if (_surface == NULL) {

		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}

	// Prevent stretching of the text
	dstRect->w = _surface->w;
	dstRect->h = _surface->h;

	SDL_RenderCopy(_renderer, _texture, NULL, dstRect);

	SDL_FreeSurface(_surface);
	SDL_DestroyTexture(_texture);
}

void Interface::displayRect(SDL_Rect* rect, SDL_Color color) {
	
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, 0);
	SDL_RenderFillRect(_renderer, rect);
}