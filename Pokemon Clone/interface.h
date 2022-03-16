#include <SDL.h>
#include <SDL_image.h>
#include <map>

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

	void setWindowWidth(int w);
	void setWindowHeight(int h);

	void addButton(std::string button, SDL_Rect* srcRect, SDL_Rect* _hoverRect, SDL_Rect* dstRect, std::string image);
	void displayButton(std::string button);
	bool isButtonHovered(SDL_Point mousePos, std::string button);

private:

	// Game UI
	SDL_Window* _window;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;

	struct Button
	{
		// CLip of the source image to be made into a button
		SDL_Rect _srcRect;

		// Appearance of the images while mouse hovers over it
		SDL_Rect _hoverRect;
		// Destination that button will be drawn on screen
		SDL_Rect _dstRect;

		// Image that button is from
		std::string _image;
	};

	// Holds buttons with key = button name
	std::map<std::string, Button> _buttons; 
};