// Board.h : represents the game board
#pragma once
#include "Location.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Board
{
public:
	Board() = delete;
	Board(std::string filename);

	void printBoard();

	bool loadNextBoard();
	void readBoardData();

	Location getPlayerLocation();
	Location getCatAtIndex(int index);
	size_t getCatVectorSize();

	int getCheese() const { return m_cheese; }
	int getLevel() const { return m_level; }
	int getKeys() const { return m_keys; }
	int getPoints() const { return m_points; }
	int getLives() const { return m_lives; }

	void incLevel() { m_level++; }
	void decCheese() { m_cheese--; }
	void decLife() { m_lives--; }
	void setKeys(int n) { m_keys = n; }
	void addPoints(int points) { m_points += points; }

	char getObjectAt(Location);
	void insertObject(Location, char);
	void clearObject(Location);

	int getSizeRows() const;
	int getSizeCols() const;

private:
	int m_rows = 0; // map size
	int m_cols = 0;  // map size

	int m_level = 0; // level number
	int m_cheese = 0; // number of pieces of cheese left

	int m_keys = 0; // number of keys; Suggestion: belongs to class Player
	int m_lives = 3; // number of lives; Suggestion: belongs to class Player
	int m_points = 0; // number of points; Suggestion: belongs to class Player

	std::ifstream m_file;
	std::vector<std::string> m_currBoard;

	Location m_playerLocation; // Player location at load time
	std::vector<Location> m_catsLocations; // Cats locations at load time
};