//////////////////////////////////////////////////////////////////////////////////
// 
// gameUI.cpp
// Jay-Mark Pascua
// 02/18/2022
// 
// Holds display-to-screen functions
//
//////////////////////////////////////////////////////////////////////////////////

#include "game.h"

void Game::displayPokemon(std::string id) {

	std::string filepath;
	SDL_Rect pokemon;

	// Display both pokemon at the same time if they are the same
	if (_playerPokemon.id == id && _opponentPokemon.id == id) {

		filepath = "assets/pokemon/sprites/" + id + ".png";
		pokemon = _opponentPokemonRect;

		_interface.render(NULL, &pokemon, filepath);

		filepath = "assets/pokemon/sprites/back/" + id + ".png";
		pokemon = _playerPokemonRect;
	}
	// Else if it's the player's pokemon, display the back of sprite
	else if (_playerPokemon.id == id) {

		filepath = "assets/pokemon/sprites/back/" + id + ".png";
		pokemon = _playerPokemonRect;
	}
	// Else display the opponent's pokemon
	else if (_opponentPokemon.id == id) {

		filepath = "assets/pokemon/sprites/" + id + ".png";
		pokemon = _opponentPokemonRect;
	}


	_interface.render(NULL, &pokemon, filepath);
}

void Game::displayAttackInfo(Attack atk) {

	_interface.displayText(atk.getElementType(), &elementTypeTxt, white);
	_interface.displayText(atk.getDamageType(), &damageTypeTxt, white);
	_interface.displayText(std::to_string(atk.tempPP) + "/" + std::to_string(atk.getPP()), &ppTxt, white);
}