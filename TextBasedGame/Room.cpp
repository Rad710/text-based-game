#include "Room.h"
#include"Bolt.h"

namespace
{
	template<class T>
	void insertToMap(const std::string& s, T* p,
		std::unordered_multimap<std::string, std::unique_ptr<T>>& map)
	{
		std::string key = s;
		key[0] = ::tolower(key[0]);
		map.insert({ key, std::unique_ptr<T>(p) });
	}
}

Room::Room(std::string newName, std::string text, 
	std::initializer_list<Item*> list, std::initializer_list<Enemy*> enemy) : 
	name(newName), description(std::move(text)), left(nullptr), 
	forward(nullptr), right(nullptr), backwards(nullptr)
{
	actions.insert({ "help", "inspect", "equip", "unequip", "go", "use", "throw",
		"die", "pick", "talk", "talk", "attack"});

	for (auto& it : list)
	{
		std::string key = it->getName();
		key[0] = ::tolower(key[0]);
		items.insert({ key, std::unique_ptr<Item>(it) });
	}

	for (auto& it : enemy)
	{
		std::string key = it->getName();
		key[0] = ::tolower(key[0]);
		enemies.insert({ key, std::unique_ptr<Enemy>(it) });
	}
}

void Room::insertItem(std::unique_ptr<Item> item) //Pre: item can be nullptr
{
	if (item)
	{
		std::string key = item->getName();
		key[0] = tolower(key[0]);

		auto p = items.try_emplace(std::move(key), std::move(item));
		if (!p.second)
		{
			dynamic_cast<Bolt*>(p.first->second.get())->increaseQuantity(
				dynamic_cast<Bolt*>(item.get())->getQuantity());
		}
	}
}

Room* Room::link(std::string& direction)
{
	if (direction == "left")
		return left;
	else if (direction.find("forward") != std::string::npos)
		return forward;
	else if (direction == "right")
		return right;
	else if (direction.find("backward") != std::string::npos)
		return backwards;

	return nullptr;
}

std::unordered_map<std::string, std::unique_ptr<Item>>::iterator
	Room::findItem(std::string& item, bool& valid)
{
	auto it = items.find(item);
	if (it != items.end())
		valid = true;
	else
		valid = false;
	return it;
}

std::unordered_multimap<std::string, std::unique_ptr<Enemy>>::iterator
	Room::findEnemy(std::string& enemy, bool& valid)
{
	auto it = enemies.find(enemy);
	if (it != enemies.end())
		valid = true;
	else
		valid = false;
	return it;
}

std::unordered_set<std::string>::iterator
	Room::findAction(std::string& action, bool& valid)
{
	auto it = actions.find(action);
	if (it != actions.end())
		valid = true;
	else
		valid = false;
	return it;
}

void Room::removeItem(std::unordered_multimap<std::string, 
	std::unique_ptr<Item>>::iterator it)
{
	items.erase(it);
}

void Room::removeEnemy(std::unordered_multimap<std::string,
	std::unique_ptr<Enemy>>::iterator it)
{
	enemies.erase(it);
}

Enemy* Room::anyEnemy() const
{
	auto enemy = enemies.begin();
	if (enemy != enemies.end())
		return enemy->second.get();

	return nullptr;
}

void Room::describe() const
{
	std::cout << "\nThe " << name << "\n\n" << description;

	for (const auto& it : items)
		std::cout << " " << it.second->getPosition();

	for (const auto& it : enemies)
		std::cout << " " << it.second->getPosition();

	std::cout << "\n\n";
}

void Room::connectToRoom(std::string way, Room& link)
{
	if (way == "left")
	{
		setLeft(link);
	}
	else if (way == "forward")
	{
		setForward(link);
	}
	else if (way == "right")
	{
		setRight(link);
	}
	else if (way == "backwards")
	{
		setBackwards(link);
	}
}