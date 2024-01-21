// Cat.cpp
#include "Cat.h"
#include "Location.h"
#include "Board.h"
#include "GameController.h"
#include <iostream> // std::cout for debugging

Cat::Cat(Location origin, Location mouse, int vectorIndex)
	: m_location(origin), m_mouseLocation(mouse), m_index(vectorIndex)
{
	m_initLocation = origin;
}

void Cat::move()
{

}

Location Cat::getLocation() const
{
	return m_location;
}

// set location to initial location
void Cat::resetLocation()
{
	
}

// set location
void Cat::setLocation(Location loc)
{
	m_location = loc;
}
 
// get mouse location
Location Cat::getPlayerLocation() const
{
	return m_mouseLocation;
}

// set mouse location
void Cat::setPlayerLocation(Location loc)
{
	m_mouseLocation = loc; //m_board.getPlayerLocation()
}

