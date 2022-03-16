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

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include "interface.h"

class Game
{
	// Initialization
	void initPokemon();
	void initAttackList();
	void initImages();
	void initButtons();

	// Game States


public:
	Game();
	~Game();

	void run();
	void handleButtonEvents(SDL_Event& e);

private:

	bool _quitGame = false;

	// Game Data
	struct Pokemon
	{
		std::string id;
		std::string name;
		std::string type1;
		std::string type2;
		int maxHp;
		int hp;
		int atk;
		int def;
		int spAtk;
		int spDef;
		int speed;
	};

	enum class menuState
	{
		MAIN = 0,
		FIGHT,
		ITEMS,
		STATS,
		RUN
	};

	menuState _menuState;

	std::map<std::string, Pokemon> _pokedex;

	// Game Window
	Interface _interface;
	int _windowWidth;
	int _windowHeight;
};

#endif