#pragma once
#include "Weapon.h"

enum class Condition //tag
{
	broken, rusty, goodCondition
};

class Sword : public Weapon
{
public:
	Sword(std::string name, int damage, Condition condition,
		std::string position = "") : Weapon(name, damage, ItemType::sword, position),
		condition(condition), numberHits(0) {}

	virtual void printName() const;

	virtual int damage() override;

	virtual void describe() const override;

	void breakSword();

	Condition getCondition() { return condition; }

private:
	Condition condition;
	int numberHits;
};

