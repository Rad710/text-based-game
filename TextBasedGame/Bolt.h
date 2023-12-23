#pragma once
#include"Item.h"

class Bolt : public Item
{
public:
	Bolt(std::string name, int newQuantity, std::string dir = "") :
		Item(name, ItemType::bolt, dir), quantity(newQuantity) {}

	int getQuantity() { return quantity; }

	void increaseQuantity(int newQuantity) { quantity += newQuantity; }

	virtual void printName() const override 
	{ std::cout << getName() << " (" << quantity << ")\n"; }

	virtual void describe() const override
	{ std::cout << "\nBolts that can be shot with a Crossbow.\n\n"; }

private:
	int quantity;
};

