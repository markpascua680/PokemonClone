#include "game.h"

void Game::initPokemon() { // Load the pokemon from database

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

void Game::initAttackList() {

}

void Game::initButtons() {

	SDL_Rect fightButton = { 10, 0, 119, 45 };
	SDL_Rect fightButtonDstRect = { _windowWidth * 0.55, _windowHeight - 120, 160, 90 };
	_interface.addButton("Fight", &fightButton, &fightButtonDstRect, "assets/BattleUI/battleCommandButtons.png");
}

Game::Game() {

	_windowWidth = _interface.WINDOW_WIDTH;
	_windowHeight = _interface.WINDOW_HEIGHT;

	initPokemon();
	initAttackList();
	initButtons();
}

Game::~Game() {

	SDL_Quit();
}

void Game::run() {

	SDL_Event e;
	menuState mState = menuState::MAIN;

	while (!_quitGame) {

		_interface.clear();

		_windowWidth = _interface.WINDOW_WIDTH;
		_windowHeight = _interface.WINDOW_HEIGHT;

		SDL_Rect battlefield = { 0, 0, _windowWidth, _windowHeight - 150 };
		SDL_Rect menu = { 0, _windowHeight - 150, _windowWidth, 150 };
		SDL_Rect playerPokemonDstRect = { _windowWidth * 0.15, _windowHeight - 540, 500, 400 };
		SDL_Rect opponentPokemonDstRect = { _windowWidth * 0.60, _windowHeight / 4, 500, 400};

		SDL_Rect fightButton = { 10, 0, 119, 45 };
		SDL_Rect fightButtonHover = { 140, 0, 249, 45 };
		SDL_Rect fightButtonDstRect = { _windowWidth * 0.55, _windowHeight - 120, 160, 90 };
		SDL_Rect pokemonButton = { 10, 46, 119, 45 };
		SDL_Rect pokemonButtonHover = { 140, 46, 249, 45 };
		SDL_Rect pokemonButtonDstRect = { _windowWidth * 0.65, _windowHeight - 120, 160, 90 };
		SDL_Rect bagButton = { 10, 92, 119, 45 };
		SDL_Rect bagButtonHover = { 140, 92, 249, 45 };
		SDL_Rect bagButtonDstRect = { _windowWidth * 0.75, _windowHeight - 120, 160, 90 };
		SDL_Rect runButton = { 10, 138, 119, 45 };
		SDL_Rect runButtonHover = { 140, 138, 249, 45 };
		SDL_Rect runButtonDstRect = { _windowWidth * 0.85, _windowHeight - 120, 160, 90 };

		// Render battlefield background
		_interface.render(NULL, &battlefield, "assets/BattleUI/battleBackground.png");

		// Render Pokemon
		_interface.render(NULL, &playerPokemonDstRect, "assets/pokemon/sprites/back/6.png");
		_interface.render(NULL, &opponentPokemonDstRect, "assets/pokemon/sprites/1.png");

		// Render UI menus
		switch (mState)
		{
		case menuState::MAIN:
			_interface.render(NULL, &menu, "assets/BattleUI/battleCommand.png");

			// Render Buttons
			_interface.displayButton("Fight");
			_interface.render(&pokemonButton, &pokemonButtonDstRect, "assets/BattleUI/battleCommandButtons.png");
			_interface.render(&bagButton, &bagButtonDstRect, "assets/BattleUI/battleCommandButtons.png");
			_interface.render(&runButton, &runButtonDstRect, "assets/BattleUI/battleCommandButtons.png");
			break;

		case menuState::FIGHT:
			_interface.render(NULL, &menu, "assets/BattleUI/battleFight.png");
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

		//TODO create button handle events function
		// Button event handling
		SDL_Point mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

		if (SDL_PointInRect(&mousePos, &fightButtonDstRect)) {
			_interface.render(&fightButtonHover, &fightButtonDstRect, "assets/BattleUI/battleCommandButtons.png");
		}

		if (SDL_PointInRect(&mousePos, &pokemonButtonDstRect)) {
			std::cout << "Pokemon hovered" << std::endl;
		}

		if (SDL_PointInRect(&mousePos, &bagButtonDstRect)) {
			std::cout << "Bag hovered" << std::endl;
		}

		if (SDL_PointInRect(&mousePos, &runButtonDstRect)) {
			std::cout << "Run hovered" << std::endl;
		}

		while (SDL_PollEvent(&e) != 0) {

			// Window event handling
			if (e.type == SDL_QUIT) {
				_quitGame = true;
			}

			

			if (e.type == SDL_MOUSEBUTTONDOWN) {

				if (SDL_PointInRect(&mousePos, &fightButtonDstRect)) {
					std::cout << "Fight pressed" << std::endl;
					mState = menuState::FIGHT;
				}

				if (SDL_PointInRect(&mousePos, &pokemonButtonDstRect)) {
					std::cout << "Pokemon pressed" << std::endl;
				}

				if (SDL_PointInRect(&mousePos, &bagButtonDstRect)) {
					std::cout << "Bag pressed" << std::endl;
				}

				if (SDL_PointInRect(&mousePos, &runButtonDstRect)) {
					std::cout << "Run pressed" << std::endl;
				}
			}

			if (e.type = SDL_WINDOWEVENT) {
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					_interface.setWindowWidth(e.window.data1);
					_interface.setWindowHeight(e.window.data2);
					break;
				default:
					break;
				}
			}
		}

		// Update window
		_interface.update();

	}

}