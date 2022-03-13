#include <SDL.h>
#include <SDL_image.h>

class Interface
{
public:
	// Window Dimensions
	int WINDOW_WIDTH = 1980;
	int WINDOW_HEIGHT = 1080;

	Interface();
	~Interface();

	void render(SDL_Rect* clip, SDL_Rect* dstRect, std::string image);
	void update();

	void setWindowWidth(int w);
	void setWindowHeight(int h);

private:

	// Game UI
	SDL_Window* _window;
	SDL_Surface* _surface;
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
};

