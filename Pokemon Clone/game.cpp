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
	_gameRunning = true;

	_interface.setFontSize(24);
	_interface.setFont("assets/font/pokemonFont.ttf");

	_windowWidth = _interface.WINDOW_WIDTH;
	_windowHeight = _interface.WINDOW_HEIGHT;

	_menuState = menuState::MAIN;

	initPokemon();
	initAttackList();
	initImages();
	initButtons();

	*p1 = getRandPokemon();
	*p2 = getRandPokemon();
	*p3 = getRandPokemon();

	_opponentPokemon = getRandPokemon();
	_opponentPokemon.setAttack(_attackList["Tackle"], 0);
	_opponentPokemon.setAttack(_attackList["Growth"], 1);
	_opponentPokemon.setAttack(_attackList["VineWhip"], 2);
	_opponentPokemon.setAttack(_attackList["RazorLeaf"], 3);

	if (_playerPokemon.speed > _opponentPokemon.speed)
		_playerTurn = true;
	else
		_playerTurn = false;
}

Game::~Game() {

	SDL_Quit();
}

// Player selects from 3 random pokemon
void Game::startScreen() {
	SDL_Event e;

	_menuState = Game::menuState::START_MENU;

	while (_playerPokemon.name == "" && _gameRunning == true) {		// TODO: Complete this function
		_interface.clear();

		handleButtonEvents(e);
		displayUI();

		_interface.update();
	}

	_playerPokemon.setAttack(_attackList["Scratch"], 0);
	_playerPokemon.setAttack(_attackList["DefenseCurl"], 1);
	_playerPokemon.setAttack(_attackList["FireFang"], 2);
	_playerPokemon.setAttack(_attackList["Ember"], 3);
	makeAttackButtons();

	_menuState = menuState::MAIN;

	delete p1;
	delete p2;
	delete p3;
}

void Game::run() {

	startScreen();
	battleLoop();

}

// Button event handling
void Game::handleButtonEvents(SDL_Event& e) {
	SDL_GetMouseState(&_interface.mousePos.x, &_interface.mousePos.y);
	SDL_Point mousePos = _interface.mousePos;

	SDL_PollEvent(&e);
	// Window event handling
	if (e.type == SDL_QUIT) {
		_gameRunning = false;
	}

	switch (_menuState)
	{
	case Game::menuState::START_MENU:

		// Mouse click events
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (_interface.isButtonHovered(mousePos, selection1)) {
				_playerPokemon = *p1;
				break;
			}

			if (_interface.isButtonHovered(mousePos, selection2)) {
				_playerPokemon = *p2;
				break;
			}

			if (_interface.isButtonHovered(mousePos, selection3)) {
				_playerPokemon = *p3;
				break;
			}
		}
		break;
	case Game::menuState::MAIN:

		// Mouse click events
		if (e.type == SDL_MOUSEBUTTONDOWN) {

			if (_interface.isButtonHovered(mousePos, _interface.buttons["Fight"].dstRect)) {
				_menuState = menuState::FIGHT;
				audio.playSound(buttonClickSFX);
			}

			if (_interface.isButtonHovered(mousePos, _interface.buttons["Pokemon"].dstRect)) {
				audio.playSound(buttonClickSFX);
			}

			if (_interface.isButtonHovered(mousePos, _interface.buttons["Bag"].dstRect)) {
				audio.playSound(buttonClickSFX);
			}

			if (_interface.isButtonHovered(mousePos, _interface.buttons["Run"].dstRect)) {
				_gameRunning = false;
				audio.playSound(buttonClickSFX);
			}

			SDL_Delay(150); // Prevent multiple inputs when clicking
		}
		break;

	// Player chooses to use an attack
	case Game::menuState::FIGHT:
		
		// Mouse click/hover events

		if (_interface.isButtonHovered(mousePos, _interface.buttons["Attack 1"].dstRect)) {

			displayAttackInfo(_playerPokemon.attacks[0]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				audio.playSound(buttonClickSFX);
				useAttack(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[0]);
				_playerTurn = false;
			}
		}

		if (_interface.isButtonHovered(mousePos, _interface.buttons["Attack 2"].dstRect)) {


			displayAttackInfo(_playerPokemon.attacks[1]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				audio.playSound(buttonClickSFX);
				useAttack(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[1]);
				_playerTurn = false;
			}
		}

		if (_interface.isButtonHovered(mousePos, _interface.buttons["Attack 3"].dstRect)) {

			displayAttackInfo(_playerPokemon.attacks[2]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				audio.playSound(buttonClickSFX);
				useAttack(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[2]);
				_playerTurn = false;
			}
		}

		if (_interface.isButtonHovered(mousePos, _interface.buttons["Attack 4"].dstRect)) {

			displayAttackInfo(_playerPokemon.attacks[3]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				audio.playSound(buttonClickSFX);
				useAttack(_playerPokemon, _opponentPokemon, _playerPokemon.attacks[3]);
				_playerTurn = false;
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