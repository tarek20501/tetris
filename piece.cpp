#include "piece.h"
#include <random>


using Offsets = const std::array<Location, 3>;
using Pieces = const std::array<Offsets, (size_t)PieceType::NumberOfPieces>;
using PiecesRotated = const std::array<Pieces, (size_t)PieceOrientation::NumberOfOrientation>;

std::default_random_engine engine(std::random_device{}());
std::uniform_int_distribution<int> typeDistribution(0, (int)PieceType::NumberOfPieces - 1);
std::uniform_int_distribution<int> orientationDistribution(0, (int)PieceOrientation::NumberOfOrientation - 1);


const constexpr Location rotateOffset(Location offset, PieceOrientation o)
{
	for (int i = 0; i < (int)o; i++)
	{
		int rotatedOffsetX = offset.x;
		offset.x = -offset.y;
		offset.y = rotatedOffsetX;
	}
	return offset;
}

constexpr Offsets rotatePiece(Offsets f, PieceOrientation o)
{
	return
	{
		rotateOffset(f[0], o),
		rotateOffset(f[1], o),
		rotateOffset(f[2], o),
	};
}

constexpr Pieces rotatePieces(Pieces p, PieceOrientation o)
{
	return
	{
		rotatePiece(p[0], o),
		rotatePiece(p[1], o),
		rotatePiece(p[2], o),
		rotatePiece(p[3], o),
		rotatePiece(p[4], o),
		rotatePiece(p[5], o),
		rotatePiece(p[6], o),
	};
}

constexpr Pieces pieces =
{
	Offsets{Location{ 1, 0 }, Location{ 0,-1 }, Location{ 1,-1 }}, // O
	Offsets{Location{ 0,-1 }, Location{ 0,-2 }, Location{ 0,-3 }}, // I
	Offsets{Location{ 1, 0 }, Location{ 1,-1 }, Location{ 2,-1 }}, // S
	Offsets{Location{-1, 0 }, Location{-1,-1 }, Location{-2,-1 }}, // Z
	Offsets{Location{-1, 0 }, Location{-1,-1 }, Location{-1,-2 }}, // L
	Offsets{Location{ 1, 0 }, Location{ 1,-1 }, Location{ 1,-2 }}, // J
	Offsets{Location{ 0,-1 }, Location{-1,-1 }, Location{ 1,-1 }}, // T
};

PiecesRotated piecesRotated =
{
	rotatePieces(pieces, PieceOrientation::O0),
	rotatePieces(pieces, PieceOrientation::O90),
	rotatePieces(pieces, PieceOrientation::O180),
	rotatePieces(pieces, PieceOrientation::O270),
};

PieceLocations Piece::calculatePieceLocations(Location& l)
{
	return PieceLocations
	{
		l,
		l + piecesRotated[(size_t)orientation][(size_t)type][0],
		l + piecesRotated[(size_t)orientation][(size_t)type][1],
		l + piecesRotated[(size_t)orientation][(size_t)type][2]
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
	type = (PieceType)typeDistribution(engine);
	orientation = (PieceOrientation)orientationDistribution(engine);
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
