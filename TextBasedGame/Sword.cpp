#include "Sword.h"

void Sword::printName() const
{
	std::cout << getName() << ": Condition (";
	switch (condition)
	{
	case Condition::broken:
		std::cout << "Broken";
		break;
	case Condition::rusty:
		std::cout << "Rusty";
		break;
	case Condition::goodCondition:
		std::cout << "Good Condition";
		break;
	}
	std::cout << "). Damage: " << getDmg() << std::endl;
}

int Sword::damage()
{
	numberHits++;
	switch (condition)
	{
	case Condition::rusty:
		if (numberHits == 5)
		{
			breakSword();
		}
		break;
	case Condition::goodCondition:
		if (numberHits == 10)
		{
			breakSword();
		}
		break;
	}
	return getDmg();
}

void Sword::describe() const
{
	std::cout << std::endl;
	switch (condition)
	{
	case Condition::broken:
		std::cout << "A broken sword. Its sharp edges can be used to attack, but"
			<< " it won't cause much damage.\n\n";
		break;
	case Condition::rusty:
		std::cout << "Its metal has corroded over time and made"
			<< " the blade weak, can break easily and doesn't have much penetration." 
			<< " Still, it can be used to defend oneself.\n\n";
		break;
	case Condition::goodCondition:
		std::cout << "It's in great condition. Its sharp blade can cause"
			<< " great damage. The sturdy blade will not break easily, and"
			<< " can even penetrate rocks.\n\n";
		break;
	}
}

void Sword::breakSword()
{
	condition = Condition::broken; 
	setDmg(5);
	std::cout << "\nThe '" << getName() << "' broke.\n\n";
}
