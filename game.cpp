#include <iostream>
#include <Windows.h>

#include "game.h"
#include "console.h"

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

bool Game::tick()
{
	static int fall = 0;

	switch (direction)
	{
	case Direction::Left:
		field.setPieceNextLocationLeft(piece);
		direction = Direction::Neither;
		break;
	case Direction::Right:
		field.setPieceNextLocationRight(piece);
		direction = Direction::Neither;
		break;
	case Direction::Down:
	case Direction::Neither:
	default:
		break;
	}

	fall = (fall + 1) % FALL_FACTOR;
	if (fall == 0 || direction == Direction::Down)
	{
		direction = Direction::Neither;
		FieldPieceStatus status = field.setPieceNextLocationDown(piece);
		if (status == FieldPieceStatus::Settled)
		{
			piece.reset();
			// check field for complete rows
		}
		else if (status == FieldPieceStatus::NoMoreRoom)
		{
			return false;
		}
	}

	piece.move();
	return true;
}

Game::Game(): 
	direction(Direction::Neither),
	piece(),
	field()
{}

void Game::goLeft()
{
	direction = Direction::Left;
}

void Game::goRight()
{
	direction = Direction::Right;
}

void Game::goDown()
{
	direction = Direction::Down;
}
