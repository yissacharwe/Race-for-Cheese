// GameController.cpp
#include "io.h"
#include "GameController.h"
#include <iomanip> // std::setw
#include <conio.h> // direct console I/O
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std::chrono_literals; // std::this_thread::sleep_for

const std::string HOME_SCREEN = "Instructions.txt"; // display when game starts

// Class Constructor
GameController::GameController()
	: m_board("Board.txt"), m_player(m_board.getPlayerLocation())
{
	// initialize cats with their locations
	for (int i = 0; i < m_board.getCatVectorSize(); i++)
		m_cats.push_back(Cat(m_board.getCatAtIndex(i), m_board.getPlayerLocation(), i));
}

// start game
void GameController::run()
{
	// play audio
	PlaySound(TEXT("theme.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC | SND_LOOP); // length: 03:12

	printScreen(HOME_SCREEN);
	auto wait = _getch(); // wait for user to press a key

	loadNextLevel();

	// Game Loop
	for (auto exit = false; !exit; )
	{
		// render
		m_board.printBoard();
		displayInterface();

		// handleInput
		while (!turnPlayed) {
			const auto c = _getch();
			switch (c)
			{
			case 0:
			case Keys::SPECIAL_KEY:
				handleSpecialKey();
				break;

			case Keys::SPACE_BAR: // skip turn
				turnPlayed = true;
				break;

			default:
				exit = handleRegularKey(c);
				break;
			}
		}
		if (m_board.getLives() == 0)
			exit = true;
		else if (m_board.getCheese() == 0)
		{
			printLevelComplete();
			loadNextLevel();
			exit = gameComplete;
		}

	} // end for loop

	system("cls");
	if (gameComplete)
	{
		PlaySound(TEXT("victory.wav"), NULL, SND_FILENAME | SND_NODEFAULT | SND_ASYNC);
		printGameComplete();
	}
	else
		std::cout << "Game Over!\n";
	wait = _getch(); // wait for user to press a key

	return;
}

void GameController::loadNextLevel()
{
	system("cls");
	if (m_board.loadNextBoard())
	{
		m_board.incLevel(); // increase level
		m_board.readBoardData();
		m_player.setLocation(m_board.getPlayerLocation());
		m_cats.clear();
		for (int i = 0; i < m_board.getCatVectorSize(); i++)
			m_cats.push_back(Cat(m_board.getCatAtIndex(i), m_board.getPlayerLocation(), i));
	}
	else {
		gameComplete = true;
	}
}

// respond to player keyboard
void GameController::handleSpecialKey()
{
	const auto c = _getch();
	Location origin = m_player.getLocation(); // current location
	Location nextLocation; // location after move
	switch (c)
	{
	case SpecialKeys::UP:
		nextLocation = Location(origin.row - 1, origin.col);
		turnPlayed = m_player.move(*this, m_board, nextLocation);
		break;

	case SpecialKeys::DOWN:
		nextLocation = Location(origin.row + 1, origin.col);
		turnPlayed = m_player.move(*this, m_board, nextLocation);
		break;

	case SpecialKeys::LEFT:
		nextLocation = Location(origin.row, origin.col-1);
		turnPlayed = m_player.move(*this, m_board, nextLocation);
		break;

	case SpecialKeys::RIGHT:
		nextLocation = Location(origin.row, origin.col+1);
		turnPlayed = m_player.move(*this, m_board, nextLocation);
		break;

	default:
		std::cout << "Unknown special key pressed (code = " << c << ")\n";
		break;
	}
}

// returns if we should exit the program
bool GameController::handleRegularKey(int c)
{
	switch (c)
	{
	case 'A':
		std::cout << "A pressed\n";
		break;
	case 'a':
		std::cout << "a pressed\n";
		break;
	case 'q': // "pass level" cheat
		eatCheese();
		break;
	case 'w':
		std::cout << m_board.getCheese();
		break;
	case Keys::ESCAPE:
		std::cout << "Escape pressed. Exiting...\n";
		return true;
	default:
		//std::cout << "Unknown regular key pressed (code = " << c << ")\n";
		break;
	}

	return false;
}

void GameController::addPoints(int points)
{
	m_board.addPoints(points);
}

// remove cat
void GameController::removeCat()
{
	if (!m_cats.empty())
	{
		Location catLocation = m_cats.back().getLocation();
		m_board.clearObject(catLocation);
		m_cats.pop_back();
	}

	m_board.addPoints(5);
}

// increment the number of keys
void GameController::addKey()
{
	int n = m_board.getKeys();
	m_board.setKeys(n + 1);
}

// remove a key and add two points;
// if player has no keys do nothing and return false
bool GameController::openDoor()
{
	int n = m_board.getKeys();
	if (n > 0)
	{
		m_board.setKeys(n-1);
		m_board.addPoints(2);
		return true;
	}
	return false;
}

// clear all cats from board and insert them in their initial location
void GameController::refreshCats()
{
	for (int i = 0; i < m_cats.size(); i++)
	{
		// remove cat from board
		m_board.clearObject(m_cats[i].getLocation());

		// reset its location
		m_cats[i].setLocation(m_board.getCatAtIndex(i));

		// insert cat in initial location
		m_board.insertObject(m_cats[i].getLocation(), '^');
	}
}

// decrement number of cheese; add 10 points
void GameController::eatCheese()
{
	m_board.decCheese();
	m_board.addPoints(10);
}

// UserInterface Display
void GameController::displayInterface()
{
	// define User Interface Screen location
	if (m_board.getSizeRows() > Screen::INTERFACE_DISPLAY_ROW - 1) {
		Screen::setLocation(Location(m_board.getSizeRows(), 0));
	}
	else {
		Screen::setLocation(Location(Screen::INTERFACE_DISPLAY_ROW, 0));
	}
	std::cout << "\n----------------------------------------------\n";
	std::cout << std::setw(21) << " LEVEL " << m_board.getLevel();
	std::cout << "\n\n Lives: " << m_board.getLives();
	std::cout << std::setw(15) << "Keys: " << m_board.getKeys();
	std::cout << std::setw(15) << "Points: " << m_board.getPoints();
	std::cout << "\n----------------------------------------------\n";
}

// decrement number of lives
void GameController::loseLife()
{
	m_board.decLife(); // decrease life
}

// display home screen
void GameController::printScreen(std::string filename) const
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "cannot open home screen display file\n";
		return;
	}
	std::vector<std::string> homeScreen;
	auto line = std::string();

	// read home screen from file
	while (std::getline(file, line) && !line.empty())
	{
		homeScreen.push_back(line);
	}

	// print home screen
	for (int i = 0; i < homeScreen.size(); i++)
		std::cout << homeScreen[i] << std::endl;
}

// print level complete message
void GameController::printLevelComplete() const
{
	system("cls");
	// define User Interface Screen location
	if (m_board.getSizeRows() > Screen::INTERFACE_DISPLAY_ROW - 1) {
		Screen::setLocation(Location(m_board.getSizeRows(), 0));
	}
	else {
		Screen::setLocation(Location(Screen::INTERFACE_DISPLAY_ROW, 0));
	}

	std::cout << "\n------------------------------------------\n";
	std::cout << "               LEVEL COMPLETE               ";
	std::cout << "\n\n";
	std::cout << "\n------------------------------------------\n";
	std::this_thread::sleep_for(950ms);
}

// print game complete message
void GameController::printGameComplete() const
{
	system("cls");
	// define User Interface Screen location
	if (m_board.getSizeRows() > Screen::INTERFACE_DISPLAY_ROW - 1) {
		Screen::setLocation(Location(m_board.getSizeRows(), 0));
	}
	else {
		Screen::setLocation(Location(Screen::INTERFACE_DISPLAY_ROW, 0));
	}

	std::cout << "\n------------------------------------------\n";
	std::cout << "                GAME COMPLETE!              \n";
	std::cout << " SCORE: " << m_board.getPoints();
	std::cout << "\n------------------------------------------\n";
	std::this_thread::sleep_for(950ms);
}
