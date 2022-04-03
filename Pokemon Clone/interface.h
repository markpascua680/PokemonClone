#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>

struct Image
{
	// Image filepath
	std::string filepath;

	// Clip of the source image
	SDL_Rect rect;
};

class Button
{
public:
	Button();
	Button(SDL_Rect sRect, SDL_Rect hRect, SDL_Rect dRect, std::string path);
	~Button();

	// Sets where button is rendered on screen
	void setDstRect(SDL_Rect dRect) {
		dstRect = dRect;
	}
	
	// Clip of the source image to be made into a button
	SDL_Rect srcRect;

	// Appearance of the images while mouse hovers over it
	SDL_Rect hoverRect;

	// Destination that button will be drawn on screen
	SDL_Rect dstRect;

	// Image filepath that button is from
	std::string filePath;

private:

};

class Interface
{
public:
	// Window
	int WINDOW_WIDTH = 1920;
	int WINDOW_HEIGHT = 1080;
	SDL_Point mousePos;

	Interface();
	~Interface();

	void render(SDL_Rect* clip, SDL_Rect* dstRect, std::string image);
	void clear();
	void update();

	// Window Functions
	void setWindowWidth(int w);
	void setWindowHeight(int h);

	// Button Functions
	void addButton(std::string button, SDL_Rect* srcRect, SDL_Rect* _hoverRect, SDL_Rect* dstRect, std::string filePath);
	void displayButton(std::string button);
	bool isButtonHovered(SDL_Point mousePos, std::string button);

	// Image Functions
	void addImage(std::string name, SDL_Rect* rect, std::string filePath);
	void displayImage(std::string name);

	// Text Functions
	void setFont(std::string fontFile);
	void setFontSize(int size);
	void displayText(std::string text, SDL_Rect* dstRect);
	
	// Holds images with key = image name
	std::map<std::string, Image> images;

	// Holds buttons with key = button name
	std::map<std::string, Button> buttons; 

private:

	// Game UI
	SDL_Window* _window;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;

	// Font
	TTF_Font* _font;
	int _fontSize;
	SDL_Color _black = { 0, 0, 0 };
	SDL_Color _white = { 255, 255, 255 };
};