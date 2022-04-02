#include "game.h"

void Game::initPokemon() { // Load the pokemon from database

	std::ifstream pokemonData;
	pokemonData.open("data/pokemon.txt");

	// Check if file can be opened
	if (!pokemonData.is_open()) {
		std::cout << "UNABLE TO OPEN FILE" << std::endl;
		EXIT_FAILURE;
	}

	// Reads data from file in this order
	std::string id, name, type1, type2;
	int maxHp, hp, atk, def, spAtk, spDef, speed;

	std::string value; // Read each value

	std::getline(pokemonData, value); // Skip past first line of file

	while (std::getline(pokemonData, value)) {

		std::istringstream iss(value);

		iss >> id;
		iss >> name;
		iss >> type1;
		iss >> type2;
		iss >> maxHp;
		iss >> hp;
		iss >> atk;
		iss >> def;
		iss >> spAtk;
		iss >> spDef;
		iss >> speed;

		Pokemon p = { id, name, type1, type2, maxHp, hp, atk, def, spAtk, spDef, speed };

		_pokemonList[name] = p;
	}

	pokemonData.close();
}

void Game::initAttackList() {

	std::ifstream attackData;
	attackData.open("data/attacks.txt");

	// Check if file can be opened
	if (!attackData.is_open()) {
		std::cout << "UNABLE TO OPEN FILE" << std::endl;
		EXIT_FAILURE;
	}

	// Reads data from file in this order
	std::string name, elementType, damageType;
	int power, accuracy, pp;

	std::string value; // Read each value

	std::getline(attackData, value); // Skip past first line of file

	while (std::getline(attackData, value)) {

		std::istringstream iss(value);

		iss >> name;
		iss >> elementType;
		iss >> damageType;
		iss >> power;
		iss >> accuracy;
		iss >> pp;

		Attack a = { name,elementType,damageType,power,accuracy,pp };

		_attackList[name] = a;

	}

	attackData.close();
}

void Game::initImages() {

	std::ifstream imageData;
	imageData.open("data/imageRects.txt");

	// Check if file can be opened
	if (!imageData.is_open()) {
		std::cout << "UNABLE TO OPEN FILE" << std::endl;
		EXIT_FAILURE;
	}

	// Image name and filepath
	std::string name, filePath;

	// Image rectangle x, y destination coordinates and width, height
	int x, y, w, h;

	// Store these coordinates into a rectangle
	SDL_Rect image;

	std::string value; // Read each value

	std::getline(imageData, value); // Skip past first line of file

	while (std::getline(imageData, value)) {

		std::istringstream iss(value);

		iss >> name;
		iss >> filePath;
		iss >> x;
		iss >> y;
		iss >> w;
		iss >> h;

		image = { x,y,w,h };

		_interface.addImage(name, &image, filePath);
	}

	imageData.close();
}

void Game::initButtons() {

	std::ifstream buttonData;
	buttonData.open("data/buttonRects.txt");

	// Check if file can be opened
	if (!buttonData.is_open()) {
		std::cout << "UNABLE TO OPEN FILE" << std::endl;
		EXIT_FAILURE;
	}

	// Rectangle's name image source
	std::string name, image;

	// Rectangle's x, y coordinates and their width, height
	int x, y, w, h;

	// Store these coordinates into source, hovered, and destination rectangles
	SDL_Rect src, hover, dst;

	// Used to read each value
	std::string value; 

	std::getline(buttonData, value); // Skip past first line of file

	while (std::getline(buttonData, value)) {

		std::istringstream iss(value);

		iss >> name;
		iss >> image;

		// The next 4 coordinates are the source's rectangle, the 4 after are the hover's rectangle, last 4 are the destination rectangle
		for (int i = 0; i < 3; i++) {

			iss >> x;
			iss >> y;
			iss >> w;
			iss >> h;

			switch (i)
			{
			case 0:
				src = { x,y,w,h };
				break;
			case 1:
				hover = { x,y,w,h };
				break;
			case 2:
				dst = { x,y,w,h };
				break;
			default:
				break;
			}
		}

		_interface.addButton(name, &src, &hover, &dst, image);
	}

	buttonData.close();
}

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

void Game::makeAttackButtons() {

	for (int i = 0; i < 4; i++) {
		std::string type = _playerPokemon.attacks[i].getElementType();

		Button b = _interface.buttons[type];
		std::string filepath = "assets/BattleUI/battleFightButtons.png";

		switch (i)
		{
		case 0:
			b.setDstRect(atkTopLeft);
			_interface.addButton("Attack 1", &b.srcRect, &b.hoverRect, &b.dstRect, filepath);
			break;
		case 1:
			b.setDstRect(atkTopRight);
			_interface.addButton("Attack 2", &b.srcRect, &b.hoverRect, &b.dstRect, filepath);
			break;
		case 2:
			b.setDstRect(atkBottomLeft);
			_interface.addButton("Attack 3", &b.srcRect, &b.hoverRect, &b.dstRect, filepath);
			break;
		case 3:
			b.setDstRect(atkBottomRight);
			_interface.addButton("Attack 4", &b.srcRect, &b.hoverRect, &b.dstRect, filepath);
			break;
		default:
			break;
		}
	}
}

Game::Game() {

	_interface.setFontSize(14);
	_interface.setFont("assets/font/pokemonFont.ttf");

	_windowWidth = _interface.WINDOW_WIDTH;
	_windowHeight = _interface.WINDOW_HEIGHT;

	_menuState = menuState::MAIN;

	initPokemon();
	initAttackList();
	initImages();
	initButtons();

	_playerPokemon = _pokemonList["Infernape"];
	_playerPokemon.setAttack(_attackList["Scratch"], 0);
	_playerPokemon.setAttack(_attackList["FireFang"], 1);
	_playerPokemon.setAttack(_attackList["Ember"], 2);
	_playerPokemon.setAttack(_attackList["DefenseCurl"], 3);
	makeAttackButtons();

	_opponentPokemon = _pokemonList["Turtwig"];
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
		_interface.displayImage("PlayerPokemonBox");
		_interface.displayImage("OpponentPokemonBox");

		// Render UI menus
		switch (_menuState)
		{
		case menuState::MAIN:
			_interface.displayImage("Menu");

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

			_interface.displayText(_playerPokemon.attacks[0].getName(), &atkTopLeft);
			_interface.displayText(_playerPokemon.attacks[1].getName(), &atkTopRight);
			_interface.displayText(_playerPokemon.attacks[2].getName(), &atkBottomLeft);
			_interface.displayText(_playerPokemon.attacks[3].getName(), &atkBottomRight);

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
		}
		break;
	case Game::menuState::FIGHT:

		// Mouse click events
		if (e.type == SDL_MOUSEBUTTONDOWN) {

			if (_interface.isButtonHovered(mousePos, "Attack 1")) {
				_menuState = menuState::FIGHT;
			}

			if (_interface.isButtonHovered(mousePos, "Attack 2")) {
			}

			if (_interface.isButtonHovered(mousePos, "Attack 3")) {
			}

			if (_interface.isButtonHovered(mousePos, "Attack 4")) {
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