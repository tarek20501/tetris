#pragma once
#include "console.h"

struct Location
{
	int x;
	int y;
};

class Piece
{
private:
	Location currLocation;
	Location nextLocation;
	Console& console;

public:
	Piece();
	Piece& operator=(const Piece&);
	Location getRight();
	Location getLeft();
	Location getDown();
	void setNextLocation(Location l);
	Location getCurrLocation();
	void move();
};
