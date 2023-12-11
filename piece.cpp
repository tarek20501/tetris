#include "piece.h"

Piece::Piece():
	console(Console::getInstance()),
	nextLocation{WIDTH / 2 - 1, -1},
	currLocation{nextLocation}
{
	console.drawBlock(currLocation.x, currLocation.y);
}

Piece& Piece::operator=(const Piece& p)
{
	nextLocation = p.nextLocation;
	currLocation = p.currLocation;
	return *this;
}

Location Piece::getRight()
{
	return Location{
		.x = nextLocation.x + 1,
		.y = nextLocation.y
	};
}

Location Piece::getLeft()
{
	return Location{
		.x = nextLocation.x - 1,
		.y = nextLocation.y
	};
}

Location Piece::getDown()
{
	return Location{
		.x = nextLocation.x,
		.y = nextLocation.y + 1
	};
}

void Piece::setNextLocation(Location l)
{
	nextLocation = l;
}

Location Piece::getCurrLocation()
{
	return currLocation;
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
