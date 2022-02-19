//////////////////////////////////////////////////////////////////////////////////
// 
// Game.h
// Jay-Mark Pascua
// 02/18/2022
// 
// Holds initialization of game assets and window, game logic, and event handles
//
//////////////////////////////////////////////////////////////////////////////////



#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>

class Game
{
	// Initialization
	void initializePokemon();
	void initializeWindow();

	// Game States


public:
	Game();
	~Game();
	void run();

private:
	// Game Data
	struct Pokemon
	{
		std::string id;
		std::string name;
		std::string type1;
		std::string type2;
		std::string maxHp;
		std::string hp;
		std::string atk;
		std::string def;
		std::string spAtk;
		std::string spDef;
		std::string speed;
	};

	std::map<std::string, Pokemon> _pokedex;

	// Game UI
	SDL_Window* _window;
	SDL_Surface* _surface;
};



#endif