#pragma once
#include "Weapon.h"
#include "Bolt.h"

class Crossbow : public Weapon
{
public:
	Crossbow(std::string name, int damage, int ammo, std::string dir = "") :
		Weapon(name , damage, ItemType::crossbow, dir), bolts(ammo) {}

	virtual void printName() const override;

	virtual int damage() override;

	virtual void describe() const override;

	void addBolts(int ammo);

	int getBolts() { return bolts; }

private:
	int bolts;
};

