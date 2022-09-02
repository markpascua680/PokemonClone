//////////////////////////////////////////////////////////////////////////////////
// 
// init.cpp
// Jay-Mark Pascua
// 02/18/2022
// 
// Holds initialization functions of game assets
//
//////////////////////////////////////////////////////////////////////////////////

#include "game.h"

// Creates a set of buttons to be displayed for the pokemon's attacks; matches the button color with the atack element type
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
	int maxHp, tempHp, atk, def, spAtk, spDef, speed;

	std::string value; // Read each value

	std::getline(pokemonData, value); // Skip past first line of file

	while (std::getline(pokemonData, value)) {

		std::istringstream iss(value);

		iss >> id;
		iss >> name;
		iss >> type1;
		iss >> type2;
		iss >> maxHp;
		iss >> tempHp;	// Hp at pokemon level 1
		iss >> atk;
		iss >> def;
		iss >> spAtk;
		iss >> spDef;
		iss >> speed;

		Pokemon p = { id, name, type1, type2, maxHp, tempHp, atk, def, spAtk, spDef, speed };

		_pokemonList[std::stoi(id)] = p;
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

Pokemon Game::getRandPokemon() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> num(387, 493);	// Range = pokemon ids

	return _pokemonList[num(rng)];
}