#include <random>

#include "tetris.h"
#include "piece.h"
#include "pieces_data.h"

std::default_random_engine engine(std::random_device{}());
std::uniform_int_distribution<int> typeDistribution(0, (int)PieceType::NumberOfPieces - 1);
std::uniform_int_distribution<int> orientationDistribution(0, (int)PieceOrientation::NumberOfOrientation - 1);

PieceLocations Piece::calculatePieceLocations(Location& l, PieceOrientation o)
{
	
	return PieceLocations
	{
		l,
		l + piecesData[(size_t)type][(size_t)o][0],
		l + piecesData[(size_t)type][(size_t)o][1],
		l + piecesData[(size_t)type][(size_t)o][2]
	};
}

void Piece::erasePiece(Location& l, PieceOrientation& o)
{
	PieceLocations locations = calculatePieceLocations(l, o);
	for (const Location& l : locations)
	{
		console.eraseBlock(l.x, l.y);
	}
}

void Piece::drawPiece(Location& l, PieceOrientation& o)
{
	PieceLocations locations = calculatePieceLocations(l, o);
	for (const Location& l : locations)
	{
		console.drawBlock(l.x, l.y);
	}
}

Piece::Piece(): console(Console::getInstance())
{
	reset();
}

void Piece::reset()
{
	nextLocation = { WIDTH / 2 - 1, -1 };
	currLocation = nextLocation;
	type = (PieceType)typeDistribution(engine);
	nextOrientation = (PieceOrientation)orientationDistribution(engine);
	currOrientation = nextOrientation;
	drawPiece(currLocation, currOrientation);
}

PieceLocations Piece::getNextRightLocations()
{
	Location l = 
	{
		.x = nextLocation.x + 1,
		.y = nextLocation.y
	};

	return calculatePieceLocations(l, nextOrientation);
}

PieceLocations Piece::getNextLeftLocations()
{
	Location l = 
	{
		.x = nextLocation.x - 1,
		.y = nextLocation.y
	};

	return calculatePieceLocations(l, nextOrientation);
}

PieceLocations Piece::getNextDownLocations()
{
	Location l = 
	{
		.x = nextLocation.x,
		.y = nextLocation.y + 1
	};

	return calculatePieceLocations(l, nextOrientation);
}

PieceLocations Piece::getNextOrientationLocations()
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

PieceLocations Piece::getCurrLocations()
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

PieceOrientation operator++(PieceOrientation& po, int)
{
	return static_cast<PieceOrientation>((static_cast<int>(po) + 1) % static_cast<int>(PieceOrientation::NumberOfOrientation));
}