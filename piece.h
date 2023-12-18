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

enum class PieceOrientation
{
	O0 = 0,
	O90,
	O180,
	O270,
	NumberOfOrientation
};

using PieceLocations = const std::array<Location, 4>;

class Piece
{
private:
	Location currLocation;
	Location nextLocation;
	PieceType type;
	PieceOrientation orientation;
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
