#include "Crossbow.h"

void Crossbow::printName() const
{
	std::cout << "Crossbow: Bolts (" << bolts << "). Damage: " << getDmg() << std::endl;
}

int Crossbow::damage()
{
	if (bolts > 0)
	{
		bolts--;
		return getDmg();
	}
	else
	{
		std::cout << "The crossbow doesn't have ammo.\n";
		return 0;
	}
}

void Crossbow::describe() const
{
	std::cout << "\nA crossbow that can be used for shooting. The bolts have a sharp"
		<< " metal head that can penetrate hard materials.\n\n";
}

void Crossbow::addBolts(int newAmmo)
{
	if (newAmmo > 0)
		bolts += newAmmo;
}
