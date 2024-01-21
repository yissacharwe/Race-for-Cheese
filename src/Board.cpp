// Board.cpp
#include "Board.h"
#include "Location.h"
#include "io.h"
#include <sstream> // std::istringstream

// Class Constructor
Board::Board(std::string fileName) : m_file(fileName) {}

// load next board from file into m_currBoad;
// return false if end of file
bool Board::loadNextBoard()
{
	auto nextLine = std::string();
	std::getline(m_file, nextLine);

	// test for end of file
	if (nextLine == "EOF")
		return false; // reached end of file

	// read map size from the first line
	auto stream = std::istringstream(nextLine);
	stream >> m_rows >> m_cols;

	m_currBoard.clear();
	while (std::getline(m_file, nextLine) && !nextLine.empty())
	{
		m_currBoard.push_back(nextLine);
	}
	// m_currBoard contains next level

	return true;
}

// read objects locations and data
void Board::readBoardData()
{
	// clear old data
	m_catsLocations.clear();
	m_cheese = 0;

	// analyze file
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_cols; j++) {
			
			char c = getObjectAt(Location(i, j));
			switch (c)
			{
			case ('%'):
				m_playerLocation = Location(i, j);
				break;
			case ('^'):
				m_catsLocations.push_back(Location(i, j));
				break;
			case ('*'):
				m_cheese++;
				break;
			default:
				break;
			}
		}
	}
}

// print board to screen
void Board::printBoard()
{
	// position board at center
	int midRow = (Screen::INTERFACE_DISPLAY_ROW / 2) - (m_rows / 2);
	int midCol = (Screen::INTERFACE_DISPLAY_WIDTH / 2) - (m_cols / 2);

	// map size might be larger than advised
	int row = (m_rows < Screen::INTERFACE_DISPLAY_ROW) ? midRow : 1;
	int col = (m_cols < Screen::INTERFACE_DISPLAY_WIDTH) ? midCol : 1;

	//system("cls");
	
	Screen::setLocation(Location(row, 0));
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < col; j++)
			std::cout << ' ';
		std::cout << m_currBoard[i] << std::endl;
	}
}

// get initial player location
Location Board::getPlayerLocation()
{
	return m_playerLocation;
}

// return number of cats on board
size_t Board::getCatVectorSize()
{
	return m_catsLocations.size();
}

// return initial cat location by index
Location Board::getCatAtIndex(int index)
{
	return m_catsLocations[index];
}

void Board::clearObject(Location loc)
{
	m_currBoard[loc.row][loc.col] = ' ';
}
void Board::insertObject(Location loc, char c)
{
	m_currBoard[loc.row][loc.col] = c;
}
char Board::getObjectAt(Location loc)
{
	return m_currBoard[loc.row][loc.col];
}

// return board height (number of rows)
int Board::getSizeRows() const
{
	return m_rows;
}

// return board width (number of cols)
int Board::getSizeCols() const
{
	return m_cols;
}