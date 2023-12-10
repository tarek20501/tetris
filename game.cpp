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

	switch (direction)
	{
	case Direction::Left:
		piece.setLocation(piece.getLeft());
		direction = Direction::Neither;
		break;
	case Direction::Right:
		piece.setLocation(piece.getRight());
		direction = Direction::Neither;
		break;
	case Direction::Neither:
	default:
		break;
	}

	fall = (fall + 1) % FALL_FACTOR;
	if (fall == 0)
	{
		piece.setLocation(piece.getDown());
	}

	piece.move();
}

Game::Game(): 
	direction(Direction::Neither),
	piece()
{}

void Game::goLeft()
{
	direction = Direction::Left;
}

void Game::goRight()
{
	direction = Direction::Right;
}
