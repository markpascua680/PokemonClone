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
	void initializePokemon();
	void initializeAttackList();

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

	Interface _interface;
};

#endif