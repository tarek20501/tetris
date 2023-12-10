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
	Location getRight();
	Location getLeft();
	Location getDown();
	void setLocation(Location l);
	void move();
};

