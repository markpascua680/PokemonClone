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

	// NOTE: Since the only attack types currently implemented have are limited, only get random pokemon with these types for now
	*p1 = getRandPokemon();
	while (p1->type1 != "Normal" && p1->type1 != "Grass" && p1->type1 != "Fire" && p1->type1 != "Water" && p1->type1 != "Electric") {
		*p1 = getRandPokemon();
	}
	*p2 = getRandPokemon();
	while (p2->type1 != "Normal" && p2->type1 != "Grass" && p2->type1 != "Fire" && p2->type1 != "Water" && p2->type1 != "Electric" && p2->id != p1->id) {	// Ensure no duplicates
		*p2 = getRandPokemon();
	}
	*p3 = getRandPokemon();
	while (p3->type1 != "Normal" && p3->type1 != "Grass" && p3->type1 != "Fire" && p3->type1 != "Water" && p3->type1 != "Electric" && p3->id != p2->id && p3->id != p1->id) {	// Ensure no duplicates
		*p3 = getRandPokemon();
	}

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

	while (_playerPokemon.name == "" && _gameRunning == true) {		// TODO: get rid of player's awkward sprite cut off gap, create attacks for each pokemon
		_interface.clear();

		displayUI();
		handleButtonEvents(e);

		_interface.update();
	}

	_interface.clear();

	displayUI();
	handleButtonEvents(e);

	_interface.update();
	
	// Randomly assign player's attacks after they choose their pokemon
	assignAttacks(_playerPokemon);
	makeAttackButtons();

	// Assign opponent a pokemon that != player's pokemon
	_opponentPokemon = getRandPokemon();
	while (_opponentPokemon.id != _playerPokemon.id &&
		_opponentPokemon.type1 != "Normal" &&
		_opponentPokemon.type1 != "Grass" &&
		_opponentPokemon.type1 != "Fire" &&
		_opponentPokemon.type1 != "Water" &&
		_opponentPokemon.type1 != "Electric") 
	{
		_opponentPokemon = getRandPokemon();
	}
	assignAttacks(_opponentPokemon);

	_menuState = menuState::MAIN;

	delete p1;
	delete p2;
	delete p3;
}

void Game::run() {

	startScreen();

	if (_gameRunning)
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
		if (_playerPokemon.name == "" && _interface.isButtonHovered(mousePos, selection1)) {
			selection1.w = 500;
			selection1.h = 500;
			_interface.displayText("Select " + p1->name + "?", &atkTopLeftTxt, white);
		}
		else {
			selection1.w = 400;
			selection1.h = 400;
		}

		if (_playerPokemon.name == "" && _interface.isButtonHovered(mousePos, selection2)) {
			selection2.w = 500;
			selection2.h = 500;
			_interface.displayText("Select " + p2->name + "?", &atkTopLeftTxt, white);
		}
		else {
			selection2.w = 400;
			selection2.h = 400;
		}

		if (_playerPokemon.name == "" && _interface.isButtonHovered(mousePos, selection3)) {
			selection3.w = 500;
			selection3.h = 500;
			_interface.displayText("Select " + p3->name + "?", &atkTopLeftTxt, white);
		}
		else {
			selection3.w = 400;
			selection3.h = 400;
		}

		// Mouse click events
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			if (_interface.isButtonHovered(mousePos, selection1)) {
				_playerPokemon = *p1;
				audio.playSound(buttonClickSFX);
				break;
			}

			if (_interface.isButtonHovered(mousePos, selection2)) {
				_playerPokemon = *p2;
				audio.playSound(buttonClickSFX);
				break;
			}

			if (_interface.isButtonHovered(mousePos, selection3)) {
				_playerPokemon = *p3;
				audio.playSound(buttonClickSFX);
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