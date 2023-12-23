#pragma once
#include "Item.h"
class Key : public Item
{
public:
	Key(std::string name, std::string position) : Item(name, ItemType::key,
		position) {}

	virtual void printName() const override { std::cout << getName() << std::endl; }

	virtual void describe() const override
	{
		std::cout << "\nOne of the keys needed to open The Entrance's gate and "
			<< "escape.\n\n";
	}
};

