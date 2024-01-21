// Player.cpp
#include "Player.h"
#include "Board.h"
#include "Location.h"
#include "GameController.h"
#include <iostream> // std::cout for debugging

// class constructor
Player::Player(Location origin)
	: m_location(origin)
{

}

// move player to specified location
bool Player::move(GameController& game, Board& board, Location nextLocation)
{
	// board boundries
	if (nextLocation.row < 0 || nextLocation.row > board.getSizeRows() - 1 ||
		nextLocation.col < 0 || nextLocation.col > board.getSizeCols() - 1)
		return false;

	auto c = board.getObjectAt(nextLocation);
	switch (c)
	{
		case ' ': // empty
			board.clearObject(m_location);
			board.insertObject(nextLocation, '%');
			setLocation(nextLocation);
			return true;
		case '#': // wall
			return false;
		case 'D': // door
			if (!game.openDoor())
				return false;
			board.clearObject(m_location);
			board.insertObject(nextLocation, '%');
			setLocation(nextLocation);
			return true;
		case '*': // cheese
			board.clearObject(m_location);
			board.insertObject(nextLocation, '%');
			setLocation(nextLocation);
			game.eatCheese();
			return true;
		case '$': // gift
			board.clearObject(m_location);
			board.insertObject(nextLocation, '%');
			setLocation(nextLocation);
			game.removeCat();
			return true;
		case 'F': // key
			board.clearObject(m_location);
			board.insertObject(nextLocation, '%');
			setLocation(nextLocation);
			game.addKey();
			return true;
		case '^': // cat
			game.loseLife();
			if (board.getLives() > 0) // not over yet
			{
				board.clearObject(m_location);
				board.insertObject(board.getPlayerLocation(), '%'); // back to start pos
				setLocation(board.getPlayerLocation());
				game.refreshCats();
			}
			return true;
		default:
			std::cout << "unrecognized object";
			break;
	}
}

// return player location
Location Player::getLocation() const
{
	return m_location;
}

// set player location to other
void Player::setLocation(Location other)
{
	m_location = other;
}
