#pragma once
#include<string>
#include<unordered_map>

#include"Weapon.h"
#include "Crossbow.h"
#include"Room.h"
#include "Item.h"

class Enemy;

class Player
{
	friend class GameInterface;
public:
	Player(Room* spawn) : health(100), lampFuel(100),
		currentWeapon(nullptr), currentRoom(spawn), dead(false), usedKeys(0) { }

	void attack(std::unique_ptr<Enemy>& enemy, bool critic);

	void receiveDamage(int damage);

	void movement(std::string& direction);

	void use(std::string& name);

	void checkInventory();
	void equipWeapon(std::string& name);

	void unequipWeapon(std::string& name);

	void pickUp(std::unique_ptr<Item>& item);//Pre: item is never nullptr
											 //Post: leaves item dangling

	bool isDead() { return dead; }

	void nextTurn();

	static void showCommands();

	void throwItem(std::string& name);

private:
	int health;
	int lampFuel;
	int usedKeys;
	bool dead;
	std::unordered_map<std::string, std::unique_ptr<Item>> inventory;
	std::unique_ptr<Weapon> currentWeapon;
	Room *currentRoom;

	void spendFuel();
};

