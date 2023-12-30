#include "tetris.h"
#include "piece.h"
#include "pieces.h"

Piece::Locations Piece::calculatePieceLocations(Location& l, Orientation o)
{
	
	return Locations
	{
		l,
		l + Pieces::getInstance().getData()[(size_t)type][(size_t)o][0],
		l + Pieces::getInstance().getData()[(size_t)type][(size_t)o][1],
		l + Pieces::getInstance().getData()[(size_t)type][(size_t)o][2]
	};
}

void Piece::erasePiece(Location& l, Orientation& o)
{
	Locations locations = calculatePieceLocations(l, o);
	for (const Location& l : locations)
	{
		console.eraseBlock(l.x, l.y);
	}
}

void Piece::drawPiece(Location& l, Orientation& o)
{
	Locations locations = calculatePieceLocations(l, o);
	for (const Location& l : locations)
	{
		console.drawBlock(l.x, l.y);
	}
}

Piece::Piece():
	console(Console::getInstance()),
	engine(std::random_device{}()),
	typeDistribution(0, (int)Type::NumberOfPieces - 1),
	orientationDistribution(0, (int)Orientation::NumberOfOrientation - 1)
{
	reset();
}

void Piece::reset()
{
	nextLocation = { WIDTH / 2 - 1, -1 };
	currLocation = nextLocation;
	type = (Type)typeDistribution(engine);
	nextOrientation = (Orientation)orientationDistribution(engine);
	currOrientation = nextOrientation;
	drawPiece(currLocation, currOrientation);
}

Piece::Locations Piece::getNextRightLocations()
{
	Location l = 
	{
		.x = nextLocation.x + 1,
		.y = nextLocation.y
	};

	return calculatePieceLocations(l, nextOrientation);
}

Piece::Locations Piece::getNextLeftLocations()
{
	Location l = 
	{
		.x = nextLocation.x - 1,
		.y = nextLocation.y
	};

	return calculatePieceLocations(l, nextOrientation);
}

Piece::Locations Piece::getNextDownLocations()
{
	Location l = 
	{
		.x = nextLocation.x,
		.y = nextLocation.y + 1
	};

	return calculatePieceLocations(l, nextOrientation);
}

Piece::Locations Piece::getNextOrientationLocations()
{
	return calculatePieceLocations(nextLocation, nextOrientation++);
}

void Piece::setNextLocation(const Location l)
{
	nextLocation = l;
}

void Piece::setNextOrientation()
{
	nextOrientation = nextOrientation++;
}

Piece::Locations Piece::getCurrLocations()
{
	return calculatePieceLocations(currLocation, currOrientation);
}

void Piece::move()
{
	if (nextLocation.x != currLocation.x || 
		nextLocation.y != currLocation.y ||
		nextOrientation != currOrientation)
	{
		erasePiece(currLocation, currOrientation);
		drawPiece(nextLocation, nextOrientation);
		currLocation = nextLocation;
		currOrientation = nextOrientation;
	}
}

Piece::Orientation operator++(Piece::Orientation& po, int)
{
	return static_cast<Piece::Orientation>((static_cast<int>(po) + 1) % static_cast<int>(Piece::Orientation::NumberOfOrientation));
}