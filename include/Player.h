// Player.h : object controlled by user
#pragma once
#include "Location.h"
class Board;
class GameController;

class Player
{
public:
	Player(Location);
	void move(GameController&, Board&, Location);
	Location getLocation() const;
	void setLocation(Location);

private:
	Location m_location; // player location
};