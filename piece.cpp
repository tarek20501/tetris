#include "piece.h"

Piece::Piece():
	console(Console::getInstance()),
	nextLocation{0,0},
	currLocation{0,0}
{
	console.drawBlock(currLocation.x, currLocation.y);
}

Location Piece::getRight()
{
	return Location{
		.x = (currLocation.x + 1) % WIDTH,
		.y = currLocation.y
	};
}

Location Piece::getLeft()
{
	return Location{
		.x = (currLocation.x > 0) ? currLocation.x - 1 : WIDTH - 1,
		.y = currLocation.y
	};
}

Location Piece::getDown()
{
	return Location{
		.x = currLocation.x,
		.y = (currLocation.y + 1) % HEIGHT
	};
}

void Piece::setLocation(Location l)
{
	nextLocation = l;
}

void Piece::move()
{
	if (nextLocation.x != currLocation.x || nextLocation.y != currLocation.y)
	{
		console.eraseBlock(currLocation.x, currLocation.y);
		console.drawBlock(nextLocation.x, nextLocation.y);
		currLocation = nextLocation;
	}
}


