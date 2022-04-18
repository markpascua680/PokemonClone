#include <iostream>
#include "audio.h"

Audio::Audio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "FAILED TO INIT AUDIO" << std::endl;
	}
}

Audio::~Audio() {
	Mix_Quit();
}

void Audio::playSound(std::string filePath) {

	Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
	if (!sound) {
		std::cout << "Music error: " << Mix_GetError() << std::endl;
	}

	Mix_VolumeChunk(sound, 10);
	Mix_PlayChannel(-1, sound, 0);
}

void Audio::playMusic() {

	Mix_Music* battleMusic = Mix_LoadMUS("assets/audio/music/PokemonBattle.wav");
	if (!battleMusic) {
		std::cout << "Music error: " << Mix_GetError() << std::endl;
	}

	Mix_VolumeMusic(5);
	Mix_PlayMusic(battleMusic, -1);
}