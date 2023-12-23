#include"Enemy.h"
#include"Player.h"
#include"BlockedWay.h"

void Enemy::talk() const
{
	if (aggressive)
	{
		std::cout << "\n  - \"" << aggressiveDialogue << "\"\n\n";
	}
	else
	{
		std::cout << "\n  - \"" << passiveDialogue << "\"\n\n";
	}
}

void Enemy::attack(Player& player) const
{
	if (aggressive)
	{
		std::cout << "-----------------------------------------\n";
		std::cout << "The '" << name << "' attacked you.";
		player.receiveDamage(dmg);
		std::cout << "-----------------------------------------\n\n";
	}
}

void Enemy::receiveDamage(int damage, bool critic)
{
	if (critic)
	{
		std::cout << "Critical hit! Enemy exploded.";
		dead = true;
	}
	else
	{
		if (!aggressive)
		{
			std::cout << "  - \"" << aggroSpeech << "\"\n\n";
			aggressive = true;
		}

		hp -= damage;
		std::cout << "The '" << name << "' received " << damage << " points of damage.\n";

		if (hp <= 0)
		{
			dead = true;
		}
	}
}

std::unique_ptr<Item> Enemy::die()
{
	std::cout << "The '" << name << "' died.\n";

	if (item && item->getType() != ItemType::blockedWay)
	{
		std::cout << "It dropped: "; 
		item->printName();

		item->setPosition("Next to the remains of the '" + name + "' you lays the '"
			+ item->getName() + "'.");
	}
	return std::move(item);
}
