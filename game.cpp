#include "game.h"
#include <iostream>
#include <Windows.h>

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void SetCursorPosition(char x, char y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void Game::tick()
{
	static bool exist = true;
	SetCursorPosition(0, 0);
	if (exist)
	{
		std::cout << "[]";
	}
	else
	{
		std::cout << "  ";
	}
	exist = !exist;
}

Game::Game()
{

}