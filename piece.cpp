#include "piece.h"
#include <random>

std::default_random_engine engine(std::random_device{}());
std::uniform_int_distribution<int> distribution(0, (int)PieceType::NumberOfPieces - 1);

Pieces pieces =
{
	PieceOffsets{Location{ 1, 0 }, Location{ 0,-1 }, Location{ 1,-1 }}, // O
	PieceOffsets{Location{ 0,-1 }, Location{ 0,-2 }, Location{ 0,-3 }}, // I
	PieceOffsets{Location{ 1, 0 }, Location{ 1,-1 }, Location{ 2,-1 }}, // S
	PieceOffsets{Location{-1, 0 }, Location{-1,-1 }, Location{-2,-1 }}, // Z
	PieceOffsets{Location{-1, 0 }, Location{-1,-1 }, Location{-1,-2 }}, // L
	PieceOffsets{Location{ 1, 0 }, Location{ 1,-1 }, Location{ 1,-2 }}, // J
	PieceOffsets{Location{ 0,-1 }, Location{-1,-1 }, Location{ 1,-1 }}, // T
};

PieceLocations Piece::calculatePieceLocations(Location& l)
{
	return PieceLocations
	{
		l,
		l + pieces[(size_t)type][0],
		l + pieces[(size_t)type][1],
		l + pieces[(size_t)type][2]
	};
}

void Piece::erasePiece(Location& l)
{
	PieceLocations locations = calculatePieceLocations(l);
	for (const Location& l : locations)
	{
		console.eraseBlock(l.x, l.y);
	}
}

void Piece::drawPiece(Location& l)
{
	PieceLocations locations = calculatePieceLocations(l);
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
	type = (PieceType)distribution(engine);
	drawPiece(currLocation);
}

PieceLocations Piece::getRight()
{
	Location l = 
	{
		.x = nextLocation.x + 1,
		.y = nextLocation.y
	};

	return calculatePieceLocations(l);
}

PieceLocations Piece::getLeft()
{
	Location l = 
	{
		.x = nextLocation.x - 1,
		.y = nextLocation.y
	};

	return calculatePieceLocations(l);
}

PieceLocations Piece::getDown()
{
	Location l = 
	{
		.x = nextLocation.x,
		.y = nextLocation.y + 1
	};

	return calculatePieceLocations(l);
}

void Piece::setNextLocation(const Location l)
{
	nextLocation = l;
}

PieceLocations Piece::getCurrLocation()
{
	return calculatePieceLocations(currLocation);
}

void Piece::move()
{
	if (nextLocation.x != currLocation.x || nextLocation.y != currLocation.y)
	{
		erasePiece(currLocation);
		drawPiece(nextLocation);
		currLocation = nextLocation;
	}
}
