#include "field.h"

bool Field::isInBounds(Location& l)
{
	if (l.x < 0 || l.x >= WIDTH)
	{
		return false;
	}
	if (l.y < 0 || l.y >= HEIGHT)
	{
		return false;
	}
	return true;
}

Field::Field(): bitmap{{false}}
{
}

void Field::setPieceNextLocationLeft(Piece& p)
{
	Location l = p.getLeft();

	if (isInBounds(l) && bitmap[l.y][l.x] == false)
	{
		p.setNextLocation(l);
	}
}

void Field::setPieceNextLocationRight(Piece& p)
{
	Location l = p.getRight();

	if (isInBounds(l) && bitmap[l.y][l.x] == false)
	{
		p.setNextLocation(l);
	}
}

FieldPieceStatus Field::setPieceNextLocationDown(Piece& p)
{
	Location l = p.getDown();

	if (!isInBounds(l) || bitmap[l.y][l.x] == true)
	{
		l = p.getCurrLocation();

		if (!isInBounds(l))
		{
			return FieldPieceStatus::NoMoreRoom;
		}

		bitmap[l.y][l.x] = true;
		return FieldPieceStatus::Settled;
	}

	p.setNextLocation(l);
	return FieldPieceStatus::Falling;
}
