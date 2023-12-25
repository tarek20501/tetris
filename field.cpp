#include <functional>
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

bool Field::isInYPlayBounds(const Location& l)
{
	if (l.y >= HEIGHT)
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

void Field::setPieceNextLocation(Piece& p, std::function<PieceLocations()> pieceLocationsMethod)
{
	PieceLocations locations = pieceLocationsMethod();

	for (const Location& l : locations)
	{
		if (!isInXBounds(l) || isCollision(l))
		{
			return;
		}
	}

	p.setNextLocation(locations[0]);
}

void Field::setPieceNextOrientation(Piece& p)
{
	PieceLocations locations = p.getNextOrientationLocations();

	for (const Location& l : locations)
	{
		if (!isInYPlayBounds(l) || !isInXBounds(l) || isCollision(l))
		{
			return;
		}
	}

	p.setNextOrientation();
}

FieldPieceStatus Field::handleFalling(Piece& p)
{
	PieceLocations locations = p.getNextDownLocations();

	for (const Location& l : locations)
	{
		if (!isInYPlayBounds(l) || isCollision(l))
		{
			PieceLocations currentLocations = p.getCurrLocations();

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
