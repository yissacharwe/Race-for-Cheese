#include "GameController.h"
#include <windows.h>

#pragma comment(lib, "Winmm.lib") // Audio

int main()
{
	// support extended ascii
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	GameController c;
	c.run();
}