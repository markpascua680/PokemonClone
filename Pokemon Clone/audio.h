#include <SDL_mixer.h>

class Audio {

public:
	Audio();
	~Audio();

	void playSound(std::string filePath);
	void playMusic();
	void pauseMusic();

private:

};

