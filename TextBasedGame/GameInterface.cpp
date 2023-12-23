#include<limits>

#include "GameInterface.h"
#include "Item.h"
#include"Enemy.h"
#include"BlockedWay.h"

namespace
{
    void standardize(std::string& input)
    {
        for (unsigned int i = 0; i < input.length(); i++)
        {
           input[i] = tolower(input[i]);
        }
    }

    std::string& upperFirstLetter(std::string& input)
    {
        input[0] = toupper(input[0]);
        return input;
    }
}

std::random_device GameInterface::rd{}; // use to seed the rng 
std::mt19937 GameInterface::rng{ rd() }; // rng

void GameInterface::play()
{
    titleScreen();

    std::stringstream ss("");
    while (true)
    {
        std::string input;

        if (!player.isDead())
        {
            std::cout << ">> Command: ";
            std::getline(std::cin, input);
            processAction(input, ss);

            if (escaped)
            {
                std::cout << "The heavy gate opens and you escape this cursed land.";
                std::cout << "\nCongratulations you won!\n\n";
                return;
            }
        }
        else
        {
            std::cout << "\nYou died! Game Over.\n\n";
            return;
        }
    }
}

void GameInterface::reset()
{
    map = Map();
    player = Player(&map[0]);
    escaped = false;
}

void GameInterface::processAction(std::string& input, std::stringstream& ss)
{
    ss.clear();
    ss << input;

    std::string action;
    std::string recipient;
    ss >> action;

    while (ss.peek() == ' ')
        ss.get();

    std::getline(ss, recipient);

    standardize(action);
    standardize(recipient);

    Room*& room = player.currentRoom;
    bool valid;
    auto command = room->findAction(action, valid);
    if (valid)
    {
        if (action == "inspect")
        {
            if (recipient == "inventory")
            {
                player.checkInventory();
                return;
            }
            else if (recipient == "room")
            {
                player.currentRoom->describe();
                return;
            }

            auto enemy = room->findEnemy(recipient, valid);
            if (valid)
            {
                enemy->second->describe();
            }
            else
            {
                auto item = room->findItem(recipient, valid);
                if (valid)
                {
                    item->second->describe();
                }
                else if ((item = player.inventory.find(recipient)) !=
                    player.inventory.end())
                {
                    item->second->describe();
                }
                else if (player.currentWeapon &&
                    player.currentWeapon->getName() == upperFirstLetter(recipient))
                {
                    player.currentWeapon->describe();
                }
                else
                {
                    std::cout << "\nCan't inspect that.\n\n";
                }
            }
        }

        else if (action == "equip")
        {
            player.equipWeapon(recipient);
        }

        else if (action == "unequip")
        {
            player.unequipWeapon(recipient);
        }

        else if (action == "go")
        {
            player.movement(recipient);
        }

        else if (action == "pick")
        {
            auto item = room->findItem(recipient, valid);
            if (valid)
            {
                player.pickUp(item->second);
                room->removeItem(item);
                player.nextTurn();
            }
            else
                std::cout << "\nCan't pick that.\n\n";
        }

        else if (action == "attack")
        {
            auto targ = room->findEnemy(recipient, valid);

            if (valid)
            {
                std::unique_ptr<Enemy>& enemy = targ->second;
                
                player.attack(enemy, criticalHit(rng));
                if (enemy->isDead())
                {
                    if (enemy->getSpecies() == EnemyType::troll)
                    {
                        auto ptr = enemy->die();
                        BlockedWay& newWay = dynamic_cast<BlockedWay&>(*ptr);

                        room->connectToRoom(newWay.getName(), newWay.getBlockedRoom());
                    }
                    else
                    {
                        room->insertItem(enemy->die());
                    }
                    room->removeEnemy(targ);
                    std::cout << "-----------------------------------------\n";
                }
                
                player.nextTurn();
            }
            else
                std::cout << "\nCan't attack that.\n\n";
        }

        else if (action == "use")
        {
            player.use(recipient);

            if (player.usedKeys == 3)
            {
                escaped = true;
            }
        }

        else if (action == "help" && recipient == "")
        {
            Player::showCommands();
        }

        else if (action == "talk")
        {
            auto enemy = room->findEnemy(recipient, valid);

            if (valid)
            {
                enemy->second->talk();
            }
            else
                std::cout << "\nYou silly, you can't talk to that!\n\n";
        }      
        else if (action == "throw")
        {
            player.throwItem(recipient);
        }
        else if (action == "die" && recipient == "")
        {
            std::cout << "\nYou lost your \033[1;33mdetermination\033[0m. "
            << "You close your eyes and perish.";
            player.dead = true;
        }
    }
    else
    {
        std::cout << "\nInvalid Command.\n\n";
    }
}

void GameInterface::titleScreen() const
{
    std::cout << "Welcome to a \"Text Based Game: The Fallen Kingdom\"\n\n";

    std::cout << "You are an adventurer that wakes up in a strange land. Your objective "
        << "is to escape before dying or before your lamp runs out of fuel. To escape "
        << "you have to find the keys that open the gate at 'The Entrance' and use them."
        << "\n\nTo play the game you must write correct commands to perform actions. "
        << "For example:\n\n >> Command: inspect inventory (this will display the items that you have "
        << "alongside your HP and the Lamp Fuel)\n\n >> Command: inspect room "
        << "(this describes current room)\n\nAlso at any time you can write \"help\""
        << " in the command line to show all existing commands.\n\nPress Enter to continue.";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("cls");
    player.currentRoom->describe();
}

bool GameInterface::gameOver()
{
    std::cout << "Would you like to play again? (yes/no): ";
    std::string input;
    std::getline(std::cin, input);
    standardize(input);

    while (true)
    {
        if (input == "yes")
        {
            system("cls");
            reset();
            return false;
        }
        else if (input == "no")
        {
            std::cout << "\nThanks for playing! :D\n";
            return true;
        }
        else
        {
            std::cout << "Read thoroughly! It's a yes or no: ";
            std::getline(std::cin, input);
            standardize(input);
        }
    }
}