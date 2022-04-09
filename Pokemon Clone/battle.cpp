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

void Game::useAttack(Pokemon& pokemon, Attack& atk) {
	
	_interface.displayImage("MessageBox");
	_interface.displayText(pokemon.name + " used " + atk.getName() + "!", &atkTopLeftTxt, white);
	_interface.update();
	SDL_Delay(1500); // Give time for player to read

	atk.tempPP--; // Subtract 1 power point
	SDL_Delay(100); // Prevent multiple inputs when clicking
}

// Applies status effect according to the move used
void Game::useStatusEffect(Pokemon& attacker, Pokemon& defender, Attack& atk) {

	std::string status = atk.getName();

	if (status == "Growth") {	// Raises attacker's attack stats
		
		attacker.atk += 5;
		attacker.spAtk += 5;
	}

	if (status == "DefenseCurl") {	// Raises attacker's defense stats

		attacker.def += 5;
		attacker.spDef += 5;
	}

	if (status == "Smokescreen") {	// Lowers defender's defense stats

		defender.def -= 5;
		defender.spDef -= 5;
	}

	if (status == "TailWhip") {		// Lowers defender's defense stats

		defender.def -= 5;
		defender.spDef -= 5;
	}

	if (status == "PlayNice") {		// Lowers defender's attack stats

		defender.atk -= 5;
		defender.spAtk -= 5;
	}

}

// Damage calculation for decreaseHealth function
double Game::calculateDamage(Pokemon& attacker, Pokemon& defender, Attack& attack) {

	double damage = 0;
	double atkStat;
	double defStat;

	if (attack.getDamageType() == "Physical") {
		
		atkStat = attacker.atk;
		defStat = defender.def;
	}

	else if (attack.getDamageType() == "Special") {

		atkStat = attacker.spAtk;
		defStat = defender.spDef;
	}

	else if (attack.getDamageType() == "Status") {
	
		useStatusEffect(attacker, defender, attack);

		return 0;
	}

		damage = 28.57 * atkStat * attack.getPower();
		damage /= defStat;
		damage /= 50;
		damage += 2;
		// damage *= type modifier / 10
		damage *= 217;
		damage /= 255;

	return damage;
}
void Game::decreaseHealth(Pokemon& pokemon, double damage) {

	if (pokemon.tempHp < damage)	// If damage is greater than remaining hp, set hp to 0
		pokemon.tempHp = 0;
	else
		pokemon.tempHp -= damage;
}