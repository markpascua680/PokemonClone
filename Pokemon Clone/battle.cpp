//////////////////////////////////////////////////////////////////////////////////
// 
// battle.cpp
// Jay-Mark Pascua
// 02/18/2022
// 
// Holds battle logic functions
//
//////////////////////////////////////////////////////////////////////////////////

#include "game.h"

void Game::useAttack(Pokemon& pokemon, Attack& atk) {
	
	_interface.displayImage("MessageBox");
	_interface.displayText(pokemon.name + " used " + atk.getName() + "!", &atkTopLeftTxt, white);
	_interface.update();
	SDL_Delay(1500); // Give time for player to read

	atk.tempPP--; // Subtract 1 power point
	SDL_Delay(100); // Prevent multiple inputs when clicking
}

void Game::decreaseHealth(Pokemon pokemon, int damage) {

	// tempHP -= 100;
	// playerHP.w *= tempHP;
	// playerHP.w /= _playerPokemon.maxHp;
}