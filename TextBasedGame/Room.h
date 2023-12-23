#pragma once
#include"Enemy.h"
#include"Item.h"

#include<unordered_map>
#include<unordered_set>
#include<initializer_list>
#include<memory>

class Room
{
public:
	Room(Room&&) noexcept = default;
	Room(std::string newName, std::string text, std::initializer_list<Item*> list, 
		std::initializer_list<Enemy*> enemy);

	void setLeft(Room& link) { left = &link; }
	void setForward(Room& link) { forward = &link; }
	void setRight(Room& link) { right = &link; }
	void setBackwards(Room& link) { backwards = &link; }

	void insertItem(std::unique_ptr<Item> item);

	Room* link(std::string& direction);

	std::unordered_map<std::string, std::unique_ptr<Item>>::iterator
		findItem(std::string& item, bool& valid);

	std::unordered_multimap<std::string, std::unique_ptr<Enemy>>::iterator
		findEnemy(std::string& enemy, bool& valid);

	std::unordered_set<std::string>::iterator
		findAction(std::string& action, bool& valid);

	void removeItem(std::unordered_map<std::string,
		std::unique_ptr<Item>>::iterator);

	void removeEnemy(std::unordered_multimap<std::string,
		std::unique_ptr<Enemy>>::iterator);

	Enemy* anyEnemy() const;

	void describe() const;

	const std::string& getName() { return name; }

	void connectToRoom(std::string way, Room& link);

private:
	std::string name;
	std::string description;

	std::unordered_map<std::string, std::unique_ptr<Item>> items;
	std::unordered_multimap<std::string, std::unique_ptr<Enemy>> enemies;
	std::unordered_set<std::string> actions;

	Room *left, *forward, *right, *backwards;
};

