#pragma once

#include <array>

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

PieceOrientation operator++(PieceOrientation& po, int);

using PieceLocations = const std::array<Location, 4>;

class Piece
{
private:
	Location currLocation;
	Location nextLocation;
	PieceType type;
	PieceOrientation currOrientation;
	PieceOrientation nextOrientation;
	Console& console;

	PieceLocations calculatePieceLocations(Location& l, PieceOrientation o);
	void erasePiece(Location& l, PieceOrientation& o);
	void drawPiece(Location& l, PieceOrientation& o);

public:
	Piece();
	void reset();
	PieceLocations getNextRightLocations();
	PieceLocations getNextLeftLocations();
	PieceLocations getNextDownLocations();
	PieceLocations getNextOrientationLocations();
	void setNextLocation(Location l);
	void setNextOrientation();
	PieceLocations getCurrLocations();
	void move();
};
