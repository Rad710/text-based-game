#pragma once
#include<random>
#include<sstream>

#include"Player.h"
#include"Map.h"

class GameInterface
{
public:
	GameInterface() : criticalHit(0.01), //probability
		map(), player(&map[0]), escaped(false) { }

	void play();
	bool gameOver();

private:
	Map map;
	Player player;
	bool escaped;

	std::bernoulli_distribution criticalHit;
	static std::random_device rd; // use to seed the rng 
	static std::mt19937 rng; // rng

	void reset();
	void processAction(std::string& input, std::stringstream& ss);
	void titleScreen() const;
};

