#pragma once

#include <random>
#include <array>
#include "console.h"

class Piece
{
public:
	struct Location
	{
		int x;
		int y;

		Location operator+(Location other)
		{
			return { x + other.x, y + other.y };
		}
	};

	enum class Type
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

	enum class Orientation
	{
		O0 = 0,
		O90,
		O180,
		O270,
		NumberOfOrientation
	};

	using Locations = const std::array<Location, 4>;

private:
	Location currLocation;
	Location nextLocation;
	Type type;
	Orientation currOrientation;
	Orientation nextOrientation;
	Console& console;
	std::default_random_engine engine;
	std::uniform_int_distribution<int> typeDistribution;
	std::uniform_int_distribution<int> orientationDistribution;

	Locations calculatePieceLocations(Location& l, Orientation o);
	void erasePiece(Location& l, Orientation& o);
	void drawPiece(Location& l, Orientation& o);

public:
	Piece();
	void reset();
	Locations getNextRightLocations();
	Locations getNextLeftLocations();
	Locations getNextDownLocations();
	Locations getNextOrientationLocations();
	void setNextLocation(Location l);
	void setNextOrientation();
	Locations getCurrLocations();
	void move();
};

Piece::Orientation operator++(Piece::Orientation& po, int);