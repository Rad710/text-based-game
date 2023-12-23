#include "Player.h"
#include"Sword.h"
#include"Consumable.h"
#include"BlockedWay.h"

void Player::attack(std::unique_ptr<Enemy>& enemy, bool critic)
{
	std::cout << "\n-----------------------------------------";
	std::cout << std::endl;
	switch (enemy->getSpecies())
	{
	case EnemyType::golem:
	case EnemyType::troll:
	case EnemyType::warrior:;
		if (!currentWeapon)
		{
			std::cout << "You feel pain in your fists.";
			receiveDamage(10);
			std::cout << std::endl;
			enemy->receiveDamage(0, false);
		}
		else if (currentWeapon->getType() == ItemType::sword)
		{
			Sword& sword = dynamic_cast<Sword&>(*currentWeapon);
			if (sword.getCondition() == Condition::rusty)
			{
				sword.breakSword();
				enemy->receiveDamage(0, false);
			}
			else if (sword.getCondition() == Condition::broken)
			{
				std::cout << "The '" << sword.getName() << "' bounces off the '"
					<< enemy->getName() << "'.\n\n";
				enemy->receiveDamage(0, false);
			}
			else
			{
				enemy->receiveDamage(currentWeapon->damage(), critic);
			}
		}
		else
		{
			enemy->receiveDamage(currentWeapon->damage(), critic);
		}
		break;

	default:
		if(!currentWeapon)
		{
			enemy->receiveDamage(1, false);
		}
		else
		{
			enemy->receiveDamage(currentWeapon->damage(), critic);
		}
	}
}

void Player::receiveDamage(int damage)
{
	health -= damage;

	std::cout << "\nYou took " << damage << " points of damage.\n";

	if (health <= 0)
	{
		dead = true;
	}
	else
		std::cout << "Current HP: " << health << std::endl;
}

void Player::movement(std::string& direction)
{
	Room* next = currentRoom->link(direction);
	if (next)
	{
		currentRoom = next;
		system("cls");
		currentRoom->describe();
		spendFuel();
	}
	else
		std::cout << "\nCan't do that.\n\n";
}

void Player::use(std::string& name)
{
	auto it = inventory.find(name);

	std::cout << std::endl;
	if (it != inventory.end())
	{
		ItemType type = it->second->getType();
		if (type == ItemType::bolt)
		{
			auto helper = inventory.find("crossbow");
			if (helper != inventory.end())
			{
				dynamic_cast<Crossbow&>(*(helper->second)).
					addBolts(dynamic_cast<Bolt&>(*(it->second)).getQuantity());

				std::cout << "You used 'Bolts'.\n\n";
				inventory.erase(it);
			}
		}
		else if (type == ItemType::consumable)
		{
			if (health < 100)
			{
				health += dynamic_cast<Consumable&>(*(it->second)).getHealPoints();
				if (health > 100)
				{
					health = 100;
				}
				std::cout << "You used '" << it->second->getName() << "'.\n";

				if (health <= 0)
				{
					health = 0;
					dead = true;
					std::cout << "You fucking donkey. Why would you do that?\n";
				}
				std::cout << "Current HP: " << health << "\n\n";
				inventory.erase(it);
			}
			else
			{
				std::cout << "HP already full.\n\n";
			}
		}
		else if (type == ItemType::key && currentRoom->getName() == "Entrance")
		{
			usedKeys++;
			std::cout << "You put the key inside one of the keyholes of the gate.\n\n";
			inventory.erase(it);
		}
		else
		{
			std::cout << "You can't use that item like that! I think you should read "
				<< "the instructions again lmao.\n\n";
		}
	}
	else
	{
		std::cout << "No can do.\n\n";
	}
}

void Player::checkInventory()
{
	std::cout << "\nHP: " << health << "\nLamp: " << lampFuel << std::endl;

	if (currentWeapon)
	{
		std::cout << "Equipped: ";
		currentWeapon->printName();
	}
	else
	{
		std::cout << "Equipped: Bare fists.\n";
	}

	std::cout << "Inventory:\n";
	for (const auto& item : inventory)
	{
		std::cout << " --> ";
		item.second->printName();
	}
	std::cout << std::endl;
}

void Player::equipWeapon(std::string& name)
{
	auto it = inventory.find(name);
	name[0] = toupper(name[0]);
	if (it != inventory.end() && (it->second->getType() == ItemType::sword
		|| it->second->getType() == ItemType::crossbow))
	{
		if (currentWeapon)
		{
			std::string key = currentWeapon->getName();
			key[0] = tolower(key[0]);
			inventory.insert({ std::move(key), std::move(currentWeapon) });
		}
		currentWeapon.reset(dynamic_cast<Weapon*>(it->second.release()));

		inventory.erase(it);
		std::cout << "\nYou equipped '" << currentWeapon->getName() << "'.\n\n";
	}
	else if (currentWeapon && name == currentWeapon->getName())
	{
		std::cout << "\nYou already have that equipped.\n\n";
	}
	else
		std::cout << "\nCan't equip that.\n\n";
}

void Player::unequipWeapon(std::string& name) //Post: currentWeapon is null iff name found
{
	name[0] = toupper(name[0]);
	if (currentWeapon && name == currentWeapon->getName())
	{
		std::cout << "\nYou unequipped '" << name << "'.\n\n";
		name[0] = tolower(name[0]);
		inventory.insert({ std::move(name), std::move(currentWeapon) });
	}
	else
	{
		std::cout << "\nCan't do that.\n\n";
	}
}

void Player::pickUp(std::unique_ptr<Item>& item) //Pre: item is never nullptr
{												//Post: leaves item dangling
	std::string key = item->getName();
	
	item->setPosition("The '" + key +
		"' lays on the floor where you threw it.");

	key[0] = tolower(key[0]);

	std::cout << "\nYou picked up '" << item->getName() << "'.\n\n";

	auto p = inventory.try_emplace(std::move(key), std::move(item));
	if (!p.second)
	{
		dynamic_cast<Bolt&>(*(p.first->second)).increaseQuantity(
			dynamic_cast<Bolt&>(*item).getQuantity());
	}
}

void Player::nextTurn()
{
	spendFuel();
	if (!dead)
	{
		Enemy* someEnemy = currentRoom->anyEnemy();
		if (someEnemy)
		{
			someEnemy->attack(*this);
		}
	}
}

void Player::showCommands()
{
	std::cout << "\n * help: shows list of commands\n"
		<< " * inspect <item>: give a description of <item>\n"
		<< " * pick <item>: picks <item>\n"
		<< " * equip <weapon>: equips a <weapon> from the inventory\n"
		<< " * unequip <weapon>: unequips an equipped <weapon>\n"
		<< " * attack <enemy>: attack <enemy>\n"
		<< " * use <item>: uses an <item> from the inventory\n"
		<< " * go <direction>: move in a <direction> ('left', 'forward', 'right', 'backwards')\n"
		<< " * talk <enemy>: strike a conversation with an <enemy>\n"
		<< " * throw <item>: throw <item> into the room\n"
		<< " * die: kill yourself\n\n";
}

void Player::throwItem(std::string& name)
{
	auto item = inventory.find(name);
	name[0] = toupper(name[0]);
	if (item != inventory.end() && item->second->getType() != ItemType::key)
	{
		std::cout << "\nYou threw '" << name << "'. It's not very useful...\n";

		auto troll = currentRoom->anyEnemy();
		if (troll && troll->getSpecies() == EnemyType::troll)
		{
			std::cout << "Aaaand the '" << troll->getName() << "' ate it. "
				<< "You truly are fantastic...\n";

			if (item->second->getType() == ItemType::consumable)
			{
				Consumable& consume= dynamic_cast<Consumable&>(*(item->second));
				if (consume.getHealPoints() < 0)
				{
					troll->receiveDamage(abs(consume.getHealPoints()), false);
					if (troll->isDead())
					{
						auto ptr = troll->die();
						BlockedWay& newWay = dynamic_cast<BlockedWay&>(*ptr);

						currentRoom->connectToRoom(newWay.getName(), newWay.getBlockedRoom());
						
						std::string s = troll->getName();
						s[0] = tolower(s[0]);
						bool b;
						currentRoom->removeEnemy(currentRoom->findEnemy(s, b));
					}
					std::cout << "\nWait. It actually worked?\n";
				}
			}
		}
		else
		{
			currentRoom->insertItem(std::move(item->second));
		}
		inventory.erase(item);
		nextTurn();
		std::cout << std::endl;
	}
	else if (currentWeapon && name == currentWeapon->getName())
	{
		std::cout << "\nYou threw '" << name << "'. It's not very useful...\n\n";

		currentRoom->insertItem(std::move(currentWeapon));
		nextTurn();
	}
	else if (name == "Lamp")
	{
		std::cout << "\nYou stupidly throw your lamp and a Demagorgon "
			<< "eats you. Well done! :D";
		dead = true;
	}
	else
	{
		std::cout << "\nYou can't throw that.\n\n";
	}
}

void Player::spendFuel()
{
	if (--lampFuel == 0)
	{
		std::cout << "You ran out of fuel. A Demagorgon ate you.";
		dead = true;
	}
}
