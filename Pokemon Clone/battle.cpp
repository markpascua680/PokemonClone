//////////////////////////////////////////////////////////////////////////////////
// 
// battle.cpp
// Jay-Mark Pascua
// 02/18/2022
// 
// Holds battle logic functions
//
//////////////////////////////////////////////////////////////////////////////////

#include "game.h"

void Game::battleLoop() {
	SDL_Event e;

	audio.playMusic();

	SDL_Delay(3500);

	_interface.clear();

	displayUI();

	_interface.update();
	SDL_Delay(2000);

	while (_gameRunning) {

		_interface.clear();

		displayUI();

		// Button event handling
		if (!_gameOver) {

			if (_playerTurn)
				handleButtonEvents(e);
			else
				opponentTurn();
		}

		// If a pokemon dies, game over
		if (_gameOver) {

			std::string message = "";
			_interface.clear();
			displayUI();
			_interface.displayImage("MessageBox");

			if (_opponentPokemon.tempHp == 0)
				message = "You won!";
			else
				message = "You lost! :(";

			_interface.displayText(message, &atkTopLeftTxt, white);

			handleButtonEvents(e);
		}
		_interface.update();
	}
}

void Game::opponentTurn() {

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> range(0, 3); // Random number between 0 - 3

	_interface.clear();
	displayUI();

	useAttack(_opponentPokemon, _playerPokemon, _opponentPokemon.attacks[range(rng)]);

	_playerTurn = true;
}

void Game::useAttack(Pokemon& attacker, Pokemon& defender, Attack& atk) {

	// Play attack SFX
	std::string filePath = "assets/audio/attackSFX/" + atk.name + ".wav";
	audio.playSound(filePath);

	// Display attack message
	std::string attackMessage = attacker.name + " used " + atk.name + "!";

	_interface.displayImage("MessageBox");
	_interface.displayText(attackMessage, &atkTopLeftTxt, white);
	_interface.update();
	SDL_Delay(1500);	// Give player time to read

	atk.tempPP--; // Subtract 1 power point

	// Animate pokemon getting hit
	if (&defender == &_playerPokemon && atk.damageType != "Status") {
		int rectX = _playerPokemonRect.x;

		for (int i = 0; i < 11; i++) {
			_playerPokemonRect.x = _windowWidth;
			SDL_Delay(20);
			animate("");
			_playerPokemonRect.x = rectX;
			animate("");
		}
	}
	if (&defender == &_opponentPokemon && atk.damageType != "Status") {
		int rectX = _opponentPokemonRect.x;

		for (int i = 0; i < 11; i++) {
			_opponentPokemonRect.x = _windowWidth;
			SDL_Delay(20);
			animate("");
			_opponentPokemonRect.x = rectX;
			animate("");
		}
	}

	// Calculate and deal damage if attack is not a status effect
	double damage = calculateDamage(attacker, defender, atk);
	decreaseHealth(defender, damage);

	defender.tempHp += (int)damage;	// Defender's HP before damage was applied

	// Animate decreasing health bar
	for (int i = 0; i < (int)damage; i++) {

		defender.tempHp--;
		animate(attackMessage);
	}

	// If pokemon fainted, animate faint
	if (_playerPokemon.tempHp == 0) {

		_gameOver = true;
		while (_playerPokemonRect.h >= 0) {

			_playerPokemonRect.y += 20;
			_playerPokemonRect.h -= 20;
			animate("");
		}
	}

	// If pokemon fainted, animate faint
	if (_opponentPokemon.tempHp == 0) {

		_gameOver = true;
		while (_opponentPokemonRect.h >= 0) {

			_opponentPokemonRect.y += 20;
			_opponentPokemonRect.h -= 20;
			animate("");
		}
	}

	_menuState = menuState::MAIN;
}

// Applies status effect according to the move used
void Game::useStatusEffect(Pokemon& attacker, Pokemon& defender, Attack& atk) {

	std::string status = atk.name;
	std::string message = "";

	if (status == "Growth") {	// Raises attacker's attack stats
		
		attacker.atk += 5;
		attacker.spAtk += 5;
		message = attacker.name + "'s attack and special attack rose!";
	}

	if (status == "DefenseCurl") {	// Raises attacker's defense stats

		attacker.def += 5;
		attacker.spDef += 5;
		message = attacker.name + "'s defense and special defense rose!";
	}

	if (status == "Smokescreen") {	// Lowers defender's defense stats

		defender.def -= 5;
		defender.spDef -= 5;
		message = defender.name + "'s defense and special defense fell!";
	}

	if (status == "TailWhip") {		// Lowers defender's defense stats

		defender.def -= 5;
		defender.spDef -= 5;
		message = defender.name + "'s defense and special defense fell!";
	}

	if (status == "PlayNice") {		// Lowers defender's attack stats

		defender.atk -= 5;
		defender.spAtk -= 5;
		message = defender.name + "'s attack and special attack fell!";
	}

	_interface.displayImage("MessageBox");
	_interface.displayText(message, &atkTopLeftTxt, white);
	_interface.update();
	SDL_Delay(2000);	// Give player time to read
}

// Damage calculation for decreaseHealth function
double Game::calculateDamage(Pokemon& attacker, Pokemon& defender, Attack& attack) {

	double damage = 0;
	double atkStat;
	double defStat;

	// Multiplies damage if the attack type is effective against defender's type
	double damageMultiplier = getDamageMultiplier(defender, attack);

	if (attack.damageType == "Physical") {
		
		atkStat = attacker.atk;
		defStat = defender.def;
	}

	else if (attack.damageType == "Special") {

		atkStat = attacker.spAtk;
		defStat = defender.spDef;
	}

	else if (attack.damageType == "Status") {
	
		useStatusEffect(attacker, defender, attack);

		return 0;
	}

		damage = 28.57 * atkStat * attack.power;
		damage /= defStat;
		damage /= 50;
		damage += 2;
		damage *= damageMultiplier;
		damage *= 217;
		damage /= 255;

		// Let player know if their attack was effective/ineffective if damage multiplier != 1
		if (damageMultiplier != 1) {

			std::string message;

			if (damageMultiplier == 0) {
				message = "It wasn't very effective...";
			}

			if (damageMultiplier == 0.5) {
				message = "It wasn't very effective...";
			}

			if (damageMultiplier == 2) {
				message = "It was super effective!";
			}

			_interface.displayImage("MessageBox");
			_interface.displayText(message, &atkTopLeftTxt, white);
			_interface.update();

			SDL_Delay(1500); // Give time for player to read
		}

	return damage;
}

// Returns a damage modifier if the type of the attack is effective against
// Defending pokemon's type. 0 for no effect, 0.5 for ineffective, 1 for indifferent, 2 for super effective
// Only accounts for the pokemon's first type, not the second if there exists one
double Game::getDamageMultiplier(Pokemon& defender, Attack& attack) {

	std::string atkType = attack.elementType;
	std::string defType = defender.type1;

	// Holds the number ID of the types of attack and defender
	int atkNum;
	int defNum;

	if (atkType == "Normal")
		atkNum = 0;
	if (atkType == "Fight")
		atkNum = 1;
	if (atkType == "Flying")
		atkNum = 2;
	if (atkType == "Poison")
		atkNum = 3;
	if (atkType == "Ground")
		atkNum = 4;
	if (atkType == "Rock")
		atkNum = 5;
	if (atkType == "Bug")
		atkNum = 6;
	if (atkType == "Ghost")
		atkNum = 7;
	if (atkType == "Steel")
		atkNum = 8;
	if (atkType == "Fire")
		atkNum = 9;
	if (atkType == "Water")
		atkNum = 10;
	if (atkType == "Grass")
		atkNum = 11;
	if (atkType == "Electric")
		atkNum = 12;
	if (atkType == "Psychic")
		atkNum = 13;
	if (atkType == "Ice")
		atkNum = 14;
	if (atkType == "Dragon")
		atkNum = 15;
	if (atkType == "Dark")
		atkNum = 16;
	if (atkType == "Fairy")
		atkNum = 17;

	if (defType == "Normal")
		defNum = 0;
	if (defType == "Fight")
		defNum = 1;
	if (defType == "Flying")
		defNum = 2;
	if (defType == "Poison")
		defNum = 3;
	if (defType == "Ground")
		defNum = 4;
	if (defType == "Rock")
		defNum = 5;
	if (defType == "Bug")
		defNum = 6;
	if (defType == "Ghost")
		defNum = 7;
	if (defType == "Steel")
		defNum = 8;
	if (defType == "Fire")
		defNum = 9;
	if (defType == "Water")
		defNum = 10;
	if (defType == "Grass")
		defNum = 11;
	if (defType == "Electric")
		defNum = 12;
	if (defType == "Psychic")
		defNum = 13;
	if (defType == "Ice")
		defNum = 14;
	if (defType == "Dragon")
		defNum = 15;
	if (defType == "Dark")
		defNum = 16;
	if (defType == "Fairy")
		defNum = 17;

	double weaknesses[18][18] = {{   1,  1,	1,	1,	1, .5,  1,  0, .5,  1,   1,   1,   1,   1,   1,   1,   1,   1},
									{	2,  1, .5, .5,  1,  2, .5,  0,  2,  1,   1,   1,   1,  .5,   2,   1,   2,  .5},
									{	1,  2,  1,  1,  1, .5,  2,  1, .5,  1,   1,   2,  .5,   1,   1,   1,   1,   1},
									{	1,  1,  1, .5, .5, .5,  1, .5,  0,  1,   1,   2,   1,   1,   1,   1,   1,   2},
									{	1,  1,  0,  2,  1,  2, .5,  1,  2,  2,   1,  .5,   2,   1,   1,   1,   1,   1},
									{	1, .5,  2,  1, .5,  1,  2,  1, .5,  2,   1,   1,   1,   1,   2,   1,   1,   1},
									{	1, .5, .5, .5,  1,  1,  1, .5, .5, .5,   1,   2,   1,   2,   1,   1,   2,  .5},
									{	0,  1,  1,  1,  1,  1,  1,  2,  1,  1,   1,   1,   1,   2,   1,   1,  .5,   1},
									{	1,  1,  1,  1,  1,  2,  1,  1, .5, .5,  .5,   1,  .5,   1,   2,   1,   1,   2},
									{	1,  1,  1,  1,  1, .5,  2,  1,  2, .5,  .5,   2,   1,   1,   2,  .5,   1,   1},
									{	1,  1,  1,  1,  2,  2,  1,  1,  1,  2,  .5,  .5,   1,   1,   1,  .5,   1,   1},
									{	1,  1, .5, .5,  2,  2, .5,  1, .5, .5,   2,  .5,   1,   1,   1,  .5,   1,   1},
									{	1,  1,  2,  1,  0,  1,  1,  1,  1,  1,   2,  .5,  .5,   1,   1,  .5,   1,   1},
									{	1,  2,  1,  2,  1,  1,  1,  1, .5,  1,   1,   1,   1,  .5,   1,   1,   0,   1},
									{	1,  1,  2,  1,  2,  1,  1,  1, .5, .5,  .5,   2,   1,   1,  .5,   2,   1,   1},
									{	1,  1,  1,  1,  1,  1,  1,  1, .5,  1,   1,   1,   1,   1,   1,   2,   1,   0},
									{	1, .5,  1,  1,  1,  1,  1,  2,  1,  1,   1,   1,   1,   2,   1,   1,  .5,  .5},
									{	1,  2,  1, .5,  1,  1,  1,  1, .5, .5,   1,   1,   1,   1,   1,   2,   2,   1}};

	double typeModifier = weaknesses[atkNum][defNum];

	return typeModifier;
}

void Game::decreaseHealth(Pokemon& pokemon, double damage) {

	if (pokemon.tempHp < damage)	// If damage is greater than remaining hp, set hp to 0
		pokemon.tempHp = 0;
	else
		pokemon.tempHp -= damage;
}