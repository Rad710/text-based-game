#pragma once
#include "Item.h"

class Weapon : public Item
{
public:
	Weapon(std::string name, int damage, ItemType type, std::string& dir) :
		Item(name, type, dir), dmg(damage) {}
	
	virtual int damage() = 0; //return damage inflicted to enemy

	void setDmg(int newDmg) { dmg = newDmg; }
	int getDmg() const { return dmg; }

private:
	int dmg;
};

