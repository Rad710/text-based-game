#pragma once
#include "Item.h"
#include"Room.h"

class BlockedWay : public Item
{
public:
	BlockedWay(Room& blockedRoom, std::string direction,
		std::string place = "") : Item(direction, ItemType::blockedWay, place),
		blockedRoom(&blockedRoom) {}

	virtual void printName() const { std::cout << getName(); }

	virtual void describe() const { std::cout << getPosition(); }

	Room& getBlockedRoom() { return *blockedRoom; }

private:
	Room* blockedRoom;
};

