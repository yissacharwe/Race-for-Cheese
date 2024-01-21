// GameController.h : manage game play
#pragma once
#include "Board.h"
#include "Player.h"
#include "Cat.h"
#include "Location.h"

class GameController
{
public:
	GameController();
	
	void run();
	void printScreen(std::string filename) const;
	void printLevelComplete() const;
	void printGameComplete() const;
	void displayInterface();
	void loseLife();
	void addPoints(int);
	void removeCat();
	void addKey();
	bool openDoor();
	void eatCheese();

	void refreshCats();

	void loadNextLevel();

	bool handleRegularKey(int c);
	void handleSpecialKey();

private:
	Board m_board;
	Player m_player;
	std::vector<Cat> m_cats;
	bool turnPlayed = false; // true when player makes a successful move

	bool gameComplete = false;
	std::string msgGameOver = "\n\n  Game Over!\n";
	std::string msgGameComplete = "\n  Game Complete!\n  Congratulations. You Win!!\n";
	std::string gameStatusBar; // Keys, Lives, Points, Level number
};