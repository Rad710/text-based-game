#pragma once
#include"Item.h"

#include<memory>

class Player;

enum class EnemyType
{
	undead, orc, skeleton, warrior, golem, troll
};

class Enemy
{
public:
	Enemy(int hp, int dmg, bool aggressive,
		EnemyType species, std::unique_ptr<Item> item, 
		std::string name, std::string position, std::string description,
		std::string aggressiveDialogue, std::string passiveDialogue = "", 
		std::string aggroSpeech = "") : dead(false), hp(hp), dmg(dmg), 
		aggressive(aggressive), species(species), item(std::move(item)), 
		name(name), position(position), description(description), 
		passiveDialogue(passiveDialogue), aggressiveDialogue(aggressiveDialogue), 
		aggroSpeech(aggroSpeech) {}

	std::string getName() const { return name; }

	const std::string& getPosition() { return position; }//Post: returns reference

	void describe() const //Prints description
	{
		std::cout << std::endl << description << std::endl << std::endl;
	}

	void talk() const;  //Prints dialogue

	void attack(Player& player) const; //Post: damages given Player obj
	void receiveDamage(int damage, bool critic); //Post: health reduced by damage amount

	bool isAggressive() const { return aggressive; }
	bool isDead() const { return dead; }

	std::unique_ptr<Item> die(); //Post: returns ptr to dropped item (can be nullptr)

	EnemyType getSpecies() const { return species; }

private:
	std::string name;
	std::string position;
	std::string description;
	std::string aggroSpeech;
	std::string passiveDialogue;
	std::string aggressiveDialogue;

	std::unique_ptr<Item> item;

	int hp;
	int dmg;
	bool dead;
	bool aggressive;

	EnemyType species;
};

