//////////////////////////////////////////////////////////////////////////////////
// 
// game.cpp
// Jay-Mark Pascua
// 02/18/2022
// 
// Holds game events
//
//////////////////////////////////////////////////////////////////////////////////

#include "game.h"

Game::Game() {

	_interface.setFontSize(24);
	_interface.setFont("assets/font/pokemonFont.ttf");

	_windowWidth = _interface.WINDOW_WIDTH;
	_windowHeight = _interface.WINDOW_HEIGHT;

	_menuState = menuState::MAIN;

	initPokemon();
	initAttackList();
	initImages();
	initButtons();
																							   
	_playerPokemon = _pokemonList["Infernape"];												   // TODO: In the future, change isButtonHovered params to (mousePos, rect)
	_playerPokemon.setAttack(_attackList["Scratch"], 0);									   // TODO: Implement damage type modifiers to calculation
	_playerPokemon.setAttack(_attackList["DefenseCurl"], 1);
	_playerPokemon.setAttack(_attackList["FireFang"], 2);
	_playerPokemon.setAttack(_attackList["Ember"], 3);
	makeAttackButtons();

	_opponentPokemon = _pokemonList["Darkrai"];
	_opponentPokemon.setAttack(_attackList["Tackle"], 0);
	_opponentPokemon.setAttack(_attackList["Growth"], 1);
	_opponentPokemon.setAttack(_attackList["VineWhip"], 2);
	_opponentPokemon.setAttack(_attackList["RazorLeaf"], 3);
}

Game::~Game() {

	SDL_Quit();
}

void Game::run() {

	SDL_Event e;

	while (!_quitGame) {

		_interface.clear();

		_windowWidth = _interface.WINDOW_WIDTH;
		_windowHeight = _interface.WINDOW_HEIGHT;

		displayUI();

		// Button event handling
		handleButtonEvents(e);

		while (SDL_PollEvent(&e) != 0) {

			// Window event handling
			if (e.type == SDL_QUIT) {
				_quitGame = true;
			}

		}

		// Update window
		_interface.update();
	}
}

// Button event handling
void Game::handleButtonEvents(SDL_Event& e) {

	SDL_Point mousePos = _interface.mousePos;

	switch (_menuState)
	{
	case Game::menuState::MAIN:

		// Mouse click events
		if (e.type == SDL_MOUSEBUTTONDOWN) {

			if (_interface.isButtonHovered(mousePos, "Fight")) {
				_menuState = menuState::FIGHT;
			}

			if (_interface.isButtonHovered(mousePos, "Pokemon")) {
			}

			if (_interface.isButtonHovered(mousePos, "Bag")) {
			}

			if (_interface.isButtonHovered(mousePos, "Run")) {
			}

			SDL_Delay(100); // Prevent multiple inputs when clicking
		}
		break;

	// Player chooses to use an attack
	case Game::menuState::FIGHT:
		
		// Mouse click/hover events

		if (_interface.isButtonHovered(mousePos, "Attack 1")) {

			displayAttackInfo(_playerPokemon.attacks[0]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				useAttack(_playerPokemon, _playerPokemon.attacks[0]);
				double damage = calculateDamage(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[0]);
				decreaseHealth(_opponentPokemon, damage);
			}
		}

		if (_interface.isButtonHovered(mousePos, "Attack 2")) {

			displayAttackInfo(_playerPokemon.attacks[1]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				
				useAttack(_playerPokemon, _playerPokemon.attacks[1]);
				double damage = calculateDamage(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[1]);
				decreaseHealth(_opponentPokemon, damage);
			}
		}

		if (_interface.isButtonHovered(mousePos, "Attack 3")) {

			displayAttackInfo(_playerPokemon.attacks[2]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				
				useAttack(_playerPokemon, _playerPokemon.attacks[2]);
				double damage = calculateDamage(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[2]);
				decreaseHealth(_opponentPokemon, damage);
			}
		}

		if (_interface.isButtonHovered(mousePos, "Attack 4")) {

			displayAttackInfo(_playerPokemon.attacks[3]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				useAttack(_playerPokemon, _playerPokemon.attacks[3]);
				double damage = calculateDamage(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[3]);
				decreaseHealth(_opponentPokemon, damage);
			}
		}		

		// Keyboard events
		if (e.type == SDL_KEYDOWN) {

			if (e.key.keysym.sym == SDLK_ESCAPE)
				_menuState = menuState::MAIN;
		}
		break;
	case Game::menuState::POKEMON:
		break;
	case Game::menuState::STATS:
		break;
	case Game::menuState::BAG:
		break;
	case Game::menuState::RUN:
		break;
	default:
		break;
	}	

}