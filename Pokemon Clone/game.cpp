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

void Game::initializeWindow() { // Open window

	// End program if fail to initialize
	if (SDL_Init(SDL_INIT_EVERYTHING < 0)) { 
		std::cout << "UNABLE TO SDL_INIT_EVERYTHING" << std::endl;
		EXIT_FAILURE;
	}

	// Create window
	_window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1980, 1080, SDL_WINDOW_SHOWN);

	if (!_window) {
		std::cout << "UNABLE TO CREATE WINDOW" << std::endl;
		EXIT_FAILURE;
	}

	// Get window surface
	_surface = SDL_GetWindowSurface(_window); 

	// Fill the screen with color white
	SDL_FillRect(_surface, NULL, SDL_MapRGB(_surface->format, 255, 255, 255));

	// Update the surface
	SDL_UpdateWindowSurface(_window);

	SDL_Delay(2000);

	// Render image to window
	SDL_Surface* image = SDL_LoadBMP("assets/pokemon/sprites.1.png");
}

Game::Game() {

}

Game::~Game() {

	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::run() {

	initializePokemon();
	initializeWindow();
}