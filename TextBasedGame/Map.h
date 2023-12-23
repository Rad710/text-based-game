#pragma once
#include<vector>
#include"Room.h"

class Map
{
public:
	Map();

	Room& operator[](int n) 
	{ return rooms.at(n); } //return reference to Room corresponding to n,
							//if invalid n throws an out_of_range exception
private:
	std::vector<Room> rooms;
};

