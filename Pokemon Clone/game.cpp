#include "game.h"

void Game::initializePokemon() { // Load the pokemon from database

	std::ifstream pokemonData;
	pokemonData.open("pokemon.txt");

	// Check if file can be opened
	if (!pokemonData.is_open()) {
		std::cout << "UNABLE TO OPEN FILE" << std::endl;
		EXIT_FAILURE;
	}

	std::string id, name, type1, type2, maxHp, hp, atk, def, spAtk, spDef, speed;

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

void Game::initializeAttackList() {

}

Game::Game() {

	initializePokemon();
	initializeAttackList();
}

Game::~Game() {

	SDL_Quit();
}

void Game::run() {
	SDL_Event e;


	while (!_quitGame) {

		SDL_Rect dstRect = { _interface.WINDOW_WIDTH / 2, _interface.WINDOW_HEIGHT / 2, 80, 80 };
		_interface.render(NULL, &dstRect, "assets/pokemon/sprites/1.png");
		_interface.update();

		while (SDL_PollEvent(&e) != 0) {

			// Window event handling
			if (e.type == SDL_QUIT) {
				_quitGame = true;
			}

			if (e.type = SDL_WINDOWEVENT) {
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					std::cout << "Window was resized!" << std::endl;
					_interface.setWindowWidth(e.window.data1);
					_interface.setWindowHeight(e.window.data2);
					break;
				default:
					break;
				}
			}
		}
	}
}