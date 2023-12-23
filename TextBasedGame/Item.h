#pragma once
#include<string>
#include<iostream>
#include<memory>

class Enemy;

enum class ItemType
{
	consumable, sword, bolt, crossbow, key, blockedWay
};

class Item
{
public:
	Item(std::string& name, ItemType type, std::string& position) : 
		name(name), type(type), position(position) {}

	virtual void printName() const = 0;

	virtual void describe() const = 0;

	void setPosition(const std::string newPosition) { position = newPosition; }
	const std::string& getPosition() const { return position; }

	std::string getName() const { return name; }
	ItemType getType() const { return type; }
	void setName(std::string newName) { name = newName; }

private:
	std::string name;
	std::string position;

	ItemType type;
};

