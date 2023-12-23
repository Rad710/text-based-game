#pragma once
#include "Item.h"

class Consumable : public Item
{
public:
	Consumable(std::string name, int points, std::string position = "") :
		Item(name, ItemType::consumable, position), healPoints(points) {}

	virtual void printName() const override { std::cout << getName() << std::endl; }

	virtual void describe() const override
	{
		std::cout << "\nUse this '" << getName() << "' to get " << healPoints 
			<< " HP.\n\n";
	}

	int getHealPoints() { return healPoints; }

private:
	int healPoints;
};

