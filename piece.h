#pragma once
#include "console.h"

struct Location
{
	int x;
	int y;

	Location operator+(Location other)
	{
		return { x + other.x, y + other.y };
	}
};

enum class PieceType
{
	O,
	I,
	S,
	Z,
	L,
	J,
	T,
	NumberOfPieces
};

using PieceLocations = const std::array<Location, 4>;
using PieceOffsets = const std::array<Location, 3>;
using Pieces = const std::array<PieceOffsets, (size_t)PieceType::NumberOfPieces>;

class Piece
{
private:
	Location currLocation;
	Location nextLocation;
	PieceType type;
	Console& console;

	PieceLocations calculatePieceLocations(Location& l);
	void erasePiece(Location& l);
	void drawPiece(Location& l);

public:
	Piece();
	void reset();
	PieceLocations getRight();
	PieceLocations getLeft();
	PieceLocations getDown();
	void setNextLocation(Location l);
	PieceLocations getCurrLocation();
	void move();
};
