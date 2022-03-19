#include "game.h"
// TODO: Find attack stats data
// TODO: Fix pokemon.txt file to correctly read data; NULL absent values
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

		_pokedex[name] = p;

	}

	pokemonData.close();
}

void Game::initAttackList() {

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

Game::Game() {

	_windowWidth = _interface.WINDOW_WIDTH;
	_windowHeight = _interface.WINDOW_HEIGHT;

	_menuState = menuState::MAIN;

	initPokemon();
	initAttackList();
	initImages();
	initButtons();
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
		_interface.displayImage("PlayerPokemon");
		_interface.displayImage("OpponentPokemon");

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
			break;
		case menuState::ITEMS:
			break;
		case menuState::STATS:
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

		// Keyboard events
		if (e.type == SDL_KEYDOWN) {

			if (e.key.keysym.sym == SDLK_ESCAPE)
				_menuState = menuState::MAIN;
		}
		break;
	case Game::menuState::ITEMS:
		break;
	case Game::menuState::STATS:
		break;
	case Game::menuState::RUN:
		break;
	default:
		break;
	}	
}