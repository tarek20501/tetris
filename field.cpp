#include "field.h"

bool Field::isInBounds(const Location& l)
{
	if (!isInXBounds(l))
	{
		return false;
	}
	if (!isInYBounds(l))
	{
		return false;
	}
	return true;
}

bool Field::isInXBounds(const Location& l)
{
	if (l.x < 0 || l.x >= WIDTH)
	{
		return false;
	}
	return true;
}

bool Field::isInYBounds(const Location& l)
{
	if (l.y < 0 || l.y >= HEIGHT)
	{
		return false;
	}
	return true;
}

bool Field::isCollision(const Location& l)
{
	if (isInBounds(l))
	{
		return bitmap[l.y][l.x];
	}
	return false;
}

Field::Field(): bitmap{{false}}
{
}

void Field::setPieceNextLocationLeft(Piece& p)
{
	PieceLocations locations = p.getLeft();

	for (const Location& l : locations)
	{
		if (!isInXBounds(l) || isCollision(l))
		{
			return;
		}
	}

	p.setNextLocation(locations[0]);
}

void Field::setPieceNextLocationRight(Piece& p)
{
	PieceLocations locations = p.getRight();

	for (const Location& l : locations)
	{
		if (!isInXBounds(l) || isCollision(l))
		{
			return;
		}
	}

	p.setNextLocation(locations[0]);
}

FieldPieceStatus Field::setPieceNextLocationDown(Piece& p)
{
	PieceLocations locations = p.getDown();

	for (const Location& l : locations)
	{
		if (l.y >= HEIGHT || isCollision(l))
		{
			PieceLocations currentLocations = p.getCurrLocation();

			for (const Location& cl : currentLocations)
			{
				if (!isInYBounds(cl))
				{
					return FieldPieceStatus::NoMoreRoom;
				}
			}

			for (const Location& cl : currentLocations)
			{
				bitmap[cl.y][cl.x] = true;
			}

			return FieldPieceStatus::Settled;
		}
	}

	p.setNextLocation(locations[0]);
	return FieldPieceStatus::Falling;
}
