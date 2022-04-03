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

void Game::decreaseHealth(Pokemon pokemon, int damage) {

	// tempHP -= 100;
	// playerHP.w *= tempHP;
	// playerHP.w /= _playerPokemon.maxHp;
}
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
																							   // TODO: Implement tempHP for pokemon
	_playerPokemon = _pokemonList["Infernape"];
	_playerPokemon.setAttack(_attackList["Scratch"], 0);
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

		// Render battlefield background
		_interface.displayImage("Battlefield");

		// Render Pokemon
		displayPokemon(_playerPokemon.id);

		if (_playerPokemon.id != _opponentPokemon.id) // Don't display opponent's pokemon if they have the same id, displayPokemon function will
			displayPokemon(_opponentPokemon.id);	  // print them both at the same time if they're the same

		// Render Pokemon HP Boxes
		_interface.displayImage("PlayerPokemonHPBox");	// Display the box template	
		_interface.displayText(_playerPokemon.name, &playerPokemonNameTxt, white);	// Display pokemon name
		_interface.displayText("Lvl. 100", &playerPokemonLevelTxt, white);	// Display pokemon level
		_interface.displayText(std::to_string(_playerPokemon.maxHp) + "/" + std::to_string(_playerPokemon.maxHp), &playerPokemonHPTxt, black);	// Display pokemon HP
		_interface.displayRect(&playerHP, green);	// Display player pokemon's HP bar

		_interface.displayImage("OpponentPokemonHPBox");
		_interface.displayText(_opponentPokemon.name, &opponentPokemonNameTxt, white);
		_interface.displayText("Lvl. 100", &opponentPokemonLevelTxt, white);
		_interface.displayText(std::to_string(_opponentPokemon.maxHp) + "/" + std::to_string(_opponentPokemon.maxHp), &opponentPokemonHPTxt, black);
		_interface.displayRect(&opponentHP, green);

		// Render UI menus
		switch (_menuState)
		{
		case menuState::MAIN:
			_interface.displayImage("Menu");
			_interface.displayText("What will you do?", &atkTopLeftTxt, white);

			// Render Buttons
			_interface.displayButton("Fight");
			_interface.displayButton("Pokemon");
			_interface.displayButton("Bag");
			_interface.displayButton("Run");
			break;

		case menuState::FIGHT:
			_interface.displayImage("FightMenu");

			// Render Buttons
			_interface.displayButton("Attack 1");
			_interface.displayButton("Attack 2");
			_interface.displayButton("Attack 3");
			_interface.displayButton("Attack 4");

			_interface.displayText(_playerPokemon.attacks[0].getName(), &atkTopLeftTxt, white);
			_interface.displayText(_playerPokemon.attacks[1].getName(), &atkTopRightTxt, white);
			_interface.displayText(_playerPokemon.attacks[2].getName(), &atkBottomLeftTxt, white);
			_interface.displayText(_playerPokemon.attacks[3].getName(), &atkBottomRightTxt, white);

			break;
		case menuState::POKEMON:
			break;
		case menuState::STATS:
			break;
		case menuState::BAG:
			break;
		case menuState::RUN:
			break;
		default:
			break;
		}

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
	case Game::menuState::FIGHT:
		
		// Mouse click/hover events

		if (_interface.isButtonHovered(mousePos, "Attack 1")) {

			displayAttackInfo(_playerPokemon.attacks[0]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				_interface.displayImage("MessageBox");
				_interface.displayText(_playerPokemon.name + " used " + _playerPokemon.attacks[0].getName() + "!", &atkTopLeftTxt, white);
				_interface.update();
				SDL_Delay(1500); // Give time for player to read

				_playerPokemon.attacks[0].tempPP--; // Subtract 1 power point
				SDL_Delay(100); // Prevent multiple inputs when clicking
			}
		}

		if (_interface.isButtonHovered(mousePos, "Attack 2")) {

			displayAttackInfo(_playerPokemon.attacks[1]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				_interface.displayImage("MessageBox");
				_interface.displayText(_playerPokemon.name + " used " + _playerPokemon.attacks[1].getName() + "!", &atkTopLeftTxt, white);
				_interface.update();
				SDL_Delay(1500); // Give time for player to read

				_playerPokemon.attacks[1].tempPP--; // Subtract 1 power point
				SDL_Delay(100); // Prevent multiple inputs when clicking
			}
		}

		if (_interface.isButtonHovered(mousePos, "Attack 3")) {

			displayAttackInfo(_playerPokemon.attacks[2]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				_interface.displayImage("MessageBox");
				_interface.displayText(_playerPokemon.name + " used " + _playerPokemon.attacks[2].getName() + "!", &atkTopLeftTxt, white);
				_interface.update();
				SDL_Delay(1500); // Give time for player to read

				_playerPokemon.attacks[2].tempPP--; // Subtract 1 power point
				SDL_Delay(100); // Prevent multiple inputs when clicking
			}
		}

		if (_interface.isButtonHovered(mousePos, "Attack 4")) {

			displayAttackInfo(_playerPokemon.attacks[3]);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				_interface.displayImage("MessageBox");
				_interface.displayText(_playerPokemon.name + " used " + _playerPokemon.attacks[3].getName() + "!", &atkTopLeftTxt, white);
				_interface.update();
				SDL_Delay(1500); // Give time for player to read

				_playerPokemon.attacks[3].tempPP--; // Subtract 1 power point
				SDL_Delay(100); // Prevent multiple inputs when clicking
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