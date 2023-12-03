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
	static int fall = 0;
	console.setCursorPosition(0, 0);

	bitMap[location.y][location.x] = false;

	switch (direction)
	{
	case Direction::Left:
		location.x = (location.x != 0) ? location.x - 1 : (WIDTH - 1);
		direction = Direction::Neither;
		break;
	case Direction::Right:
		location.x = (location.x + 1) % WIDTH;
		direction = Direction::Neither;
		break;
	case Direction::Neither:
	default:
		break;
	}

	fall = (fall + 1) % FALL_FACTOR;
	if (fall == 0)
	{
		location.y = (location.y + 1) % HEIGHT;
	}
	

	bitMap[location.y][location.x] = true;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			std::cout << bitMap[y][x];
		}
		std::cout << std::endl;
	}
}

Game::Game(): 
	command(' '), 
	console(Console::getInstance()),
	direction(Direction::Neither),
	location({0,0}),
	bitMap{ {false} }
{}

void Game::goLeft()
{
	direction = Direction::Left;
}

void Game::goRight()
{
	direction = Direction::Right;
}
