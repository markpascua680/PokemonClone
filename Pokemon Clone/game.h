//////////////////////////////////////////////////////////////////////////////////
// 
// game.h
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
#include <random>
#include "interface.h"
#include "audio.h"

// Holds attributes of each attack
	class Attack {
	public:
		int pp;		// Max number of times attack can be used
		int tempPP;	// Current number of times the attack can be used
		std::string name;
		std::string elementType;	// Fire, water, grass, etc.
		std::string damageType;		// Physical/special damage or status effects
		int power;
		int accuracy;

		Attack() {

		}

		Attack(
			std::string n,        // Name of attack
			std::string eT,        // Grass, Fire, Water, etc.
			std::string dT,    // Physical, Special, Status effect, etc.
			int p,				 // Base damage of the attack
			int a,			 // Chance of hitting attack
			int pp1					 // Power Points; how many times it can be used in battle
		) {
			name = n;
			elementType = eT;
			damageType = dT;
			power = p;
			accuracy = a;
			pp = pp1;
			tempPP = pp1;
		}

	private:

	};

	struct Pokemon
	{
		std::string id;
		std::string name;
		std::string type1;
		std::string type2;
		int maxHp;
		int tempHp;
		int atk;
		int def;
		int spAtk;
		int spDef;
		int speed;

		std::vector<Attack> attacks{ 4 }; // Each pokemon can have up to 4 attacks
	};

class Game
{
	// Initialization
	void initPokemon();
	void initAttackList();
	void initImages();
	void initButtons();

	// Setup player/opponent's pokemon their attacks
	void assignAttacks(Pokemon& p);
	Pokemon getRandPokemon();

	// Rendering
	void displayPokemon(std::string id);
	void displayAttackInfo(Attack& atk); // Shows attacks' damage type, element type, and pp counter
	void displayUI();
	void displayPokemonHPBoxes();
		// Creates a set of buttons to be displayed for the pokemon's attacks
	void makeAttackButtons();

	// Animation
	void animate(std::string attackMsg);

	// Game States
	void startScreen();
	void battleLoop();

	// Game Events
	void changePlayerPokemon(const int& id) {

		_playerPokemon = _pokemonList[id];
	}

	void changeOpponentPokemon(const int& id) {

		_opponentPokemon = _pokemonList[id];
	}
		
		// Opponent's turn
	void opponentTurn();

		// Player or opponent uses an attack
	void useAttack(Pokemon& attacker, Pokemon& defender, Attack& atk);

		// Determines the status effect of an attack that affects stats
	void useStatusEffect(Pokemon& attacker, Pokemon& defender, Attack& atk);

		// Damage calculation
	double calculateDamage(Pokemon& attacker, Pokemon& defender, Attack& attack);

		// Multiplies damage of attack based on elemental weakness
	double getDamageMultiplier(Pokemon& defender, Attack& attack);

		// Decrease pokemon HP when taking damage
	void decreaseHealth(Pokemon& pokemon, double damage);

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

	// Game Audio
	Audio audio;
	std::string buttonClickSFX = "assets/audio/misc/button_click.wav";

	// Start menu values
	Pokemon* p1 = new Pokemon;
	Pokemon* p2 = new Pokemon;
	Pokemon* p3 = new Pokemon;
	SDL_Rect selection1 = { 200, 300, 400, 400 };
	SDL_Rect selection2 = { 700, 300, 400, 400 };
	SDL_Rect selection3 = { 1200, 300, 400, 400 };

	// Player/Opponent dimensions on screen
	SDL_Rect _playerPokemonRect = { 288, 540, 400, 400 };
	SDL_Rect _opponentPokemonRect = { 1170, 250, 400, 400 };

	// Button Rects; buttons at certain positions of the fight menu
	SDL_Rect atkTopLeft = { 0, 930, 695, 80 };
	SDL_Rect atkTopRight = { 700, 930, 695, 80 };
	SDL_Rect atkBottomLeft = { 0, 1005, 695, 80 };
	SDL_Rect atkBottomRight = { 700, 1005, 695, 80 };

	// Text Boxes; width and height for these values are zero because they are set in displayText function of Interface.cpp
		// Attacking menu text boxes
	SDL_Rect atkTopLeftTxt = { 30, 940, 0, 0 };	
	SDL_Rect atkTopRightTxt = { 730, 940, 0, 0 };															 
	SDL_Rect atkBottomLeftTxt = { 30, 1015, 0, 0 };															 
	SDL_Rect atkBottomRightTxt = { 730, 1015, 0, 0 };														 
	SDL_Rect elementTypeTxt = { 1500, 940, 0, 0 };															 
	SDL_Rect damageTypeTxt = { 1500, 980, 0, 0 };															 
	SDL_Rect ppTxt = { 1500, 1020, 0, 0 };					

		// HP Box Text Boxes
	SDL_Rect playerPokemonNameTxt = { 1015, 630, 0, 0 };													 
	SDL_Rect playerPokemonHpTxt = { 1300, 780, 0, 0 };
	SDL_Rect playerPokemonLevelTxt = { 1600, 630, 0, 0 };
	SDL_Rect opponentPokemonNameTxt = { 90, 130, 0, 0 };
	SDL_Rect opponentPokemonHPTxt = { 375, 280, 0, 0 };
	SDL_Rect opponentPokemonLevelTxt = { 675, 130, 0, 0 };

	// HP Bars
	SDL_Rect playerHp = { 1096, 749, 364, 22 };
	SDL_Rect opponentHp = { 170, 249, 364, 22 };

	// Colors
	SDL_Color black = { 0, 0, 0 };	
	SDL_Color white = { 255, 255, 255 };
	SDL_Color green = { 0, 255, 0 };
	SDL_Color red = { 255, 0, 0 };

	// Game Data
	bool _gameRunning;
	bool _gameOver = false;
	bool _playerTurn;	// Determines who is attacking

	// Game States
	enum class menuState
	{
		MAIN = 0,
		FIGHT,
		POKEMON,
		STATS,
		BAG,
		RUN,
		MESSAGEBOX,
		START_MENU
	};

	menuState _menuState;

	std::map<int, Pokemon> _pokemonList;
	std::map<int, Attack> _attackList;

	Pokemon _playerPokemon;
	Pokemon _opponentPokemon;
};

#endif