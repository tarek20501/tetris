#include <iostream>

#include "game.h"

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}

bool Game::tick()
{
	static int fall = 0; // throttle falling

	switch (direction)
	{
	case Direction::Left:
		field.setPieceNextLocation(piece, std::bind(&Piece::getNextLeftLocations, &piece));
		direction = Direction::None;
		break;
	case Direction::Right:
		field.setPieceNextLocation(piece, std::bind(&Piece::getNextRightLocations, &piece));
		direction = Direction::None;
		break;
	case Direction::Rotate:
		field.setPieceNextOrientation(piece);
		direction = Direction::None;
		break;
	case Direction::Down:
	case Direction::None:
	default:
		break;
	}

	fall = (fall + 1) % FALL_FACTOR;
	if (fall == 0 || direction == Direction::Down)
	{
		direction = Direction::None;
		Field::PieceStatus status = field.handleFalling(piece);
		if (status == Field::PieceStatus::Settled)
		{
			piece.reset();
			field.eraseCompleteRows();
		}
		else if (status == Field::PieceStatus::NoMoreRoom)
		{
			return false;
		}
	}

	piece.move();
	return true;
}

Game::Game(): 
	direction(Direction::None),
	piece(Piece::getInstance()),
	field()
{}

void Game::goUp()
{
	direction = Direction::Rotate;
}

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
