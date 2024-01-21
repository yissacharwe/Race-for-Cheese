// Cat.h
#pragma once
#include "Location.h"
class Board;
class GameController;

class Cat
{
public:
	Cat() = delete;
	Cat(Location, Location, int);

	void move();

	Location getLocation() const;
	Location getPlayerLocation() const;
	void setLocation(Location);
	void setPlayerLocation(Location);
	void resetLocation();


private:
	int m_index; // index for std::vector<Location> m_catsLocations  at Board.h;
	Location m_location;
	Location m_initLocation; // also at Board.h
	Location m_mouseLocation;
};