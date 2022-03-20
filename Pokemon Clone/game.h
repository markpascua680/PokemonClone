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
#include <vector>
#include "interface.h"

class Game
{
	// Initialization
	void initPokemon();
	void initAttackList();
	void initImages();
	void initButtons();

	// Rendering
	void displayPokemon(std::string id);
	// Game States

	// Game Events
	void changePokemon(std::string name) {

		_playerPokemon = _pokemonList[name];
	}
public:
	Game();
	~Game();

	void run();
	void handleButtonEvents(SDL_Event& e);

private:

	// Game Window
	Interface _interface;
	int _windowWidth;
	int _windowHeight;

	// Player/Opponent dimensions on screen
	int _playerX = 288;
	int _playerY = 540;
	int _playerW = 500;
	int _playerH = 400;

	// Game Data
	bool _quitGame = false;

		// Holds attributes of each attack
	class Attack {
	public:
		int tempPP;

		Attack() {

		}

		Attack(
			std::string name,        // Name of attack
			std::string elementType,        // Grass, Fire, Water, etc.
			std::string damageType,    // Physical, Special, Status effect, etc.
			int power,				 // Base damage of the attack
			int accuracy,			 // Chance of hitting attack
			int pp1					 // Power Points; how many times it can be used in battle
		) {
			_name = name;
			_elementType = elementType;
			_damageType = damageType;
			_power = power;
			_accuracy = accuracy;
			_pp, tempPP = pp1;
		}

		int getPower() {
			return _power;
		}

		std::string getName() {
			return _name;
		}

		std::string getElementType() {
			return _elementType;
		}

		std::string getDamageType() {
			return _damageType;
		}

	private:
		std::string _name;
		std::string _elementType;
		std::string _damageType;
		int _power;
		int _accuracy;
		int _pp;

	};

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

		std::vector<Attack> attacks{ 4 }; // Each pokemon can have up to 4 attacks

		//Sets attack a at a certain position, up to 4 attacks can be set for one Pokemon
		void setAttack(Attack a, int position) {

			if (attacks[position].getName() == "" && position < 4) {

				attacks[position] = a;
			}
			else
				std::cout << "Do you want to replace this attack with " << a.getName() << " ? " << std::endl;
		}
	};

	// Game States
	enum class menuState
	{
		MAIN = 0,
		FIGHT,
		POKEMON,
		STATS,
		BAG,
		RUN
	};

	menuState _menuState;

	std::map<std::string, Pokemon> _pokemonList;
	std::map<std::string, Attack> _attackList;

	Pokemon _playerPokemon;
	Pokemon _opponentPokemon;
};

#endif