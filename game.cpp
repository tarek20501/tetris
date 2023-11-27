#include <iostream>
#include <Windows.h>

#include "game.h"
#include "console.h"

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

void Game::tick()
{
	static bool exist = true;
	Console::setCursorPosition(0, 0);
	if (exist)
	{
		std::cout << command;
	}
	else
	{
		std::cout << ' ';
	}
	exist = !exist;
}

Game::Game(): command(' ')
{}

void Game::loadCommand(const char c)
{
	if (command == ' ')
	{
		command = c;
	}
}

void Game::clearCommand(const char c)
{
	if (c == command)
	{
		command = ' ';
	}
}
