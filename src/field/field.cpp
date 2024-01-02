#include <functional>
#include <numeric>

#include "field.h"

bool Field::isInBounds(const Piece::Location& l)
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

bool Field::isInXBounds(const Piece::Location& l)
{
	if (l.x < 0 || l.x >= WIDTH)
	{
		return false;
	}
	return true;
}

bool Field::isInYBounds(const Piece::Location& l)
{
	if (l.y < 0 || l.y >= HEIGHT)
	{
		return false;
	}
	return true;
}

bool Field::isInYPlayBounds(const Piece::Location& l)
{
	if (l.y >= HEIGHT)
	{
		return false;
	}
	return true;
}

bool Field::isCollision(const Piece::Location& l)
{
	if (isInBounds(l))
	{
		return bitmap[l.y][l.x];
	}
	return false;
}

void Field::collapseRow(int y)
{
	for (int i = y; i > 0; i--)
	{
		bitmap[i] = bitmap[i - 1];
	}
	bitmap[0].fill(false);
}

void Field::renderTillY(int y)
{
	for (int j = 0; j <= y; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			if (bitmap[j][i])
			{
				console.drawBlock(i, j);
			}
			else
			{
				console.eraseBlock(i, j);
			}
		}
	}
}

Field::Field(): bitmap{{false}}, console(Console::getInstance())
{
}

Field& Field::getInstance()
{
	static Field singleton;

	return singleton;
}

void Field::setPieceNextLocation(Piece& p, std::function<Piece::Locations()> pieceLocationsMethod)
{
	Piece::Locations locations = pieceLocationsMethod();

	for (const Piece::Location& l : locations)
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
	Piece::Locations locations = p.getNextOrientationLocations();

	for (const Piece::Location& l : locations)
	{
		if (!isInYPlayBounds(l) || !isInXBounds(l) || isCollision(l))
		{
			return;
		}
	}

	p.setNextOrientation();
}

Field::PieceStatus Field::handleFalling(Piece& p)
{
	Piece::Locations locations = p.getNextDownLocations();

	for (const Piece::Location& l : locations)
	{
		if (!isInYPlayBounds(l) || isCollision(l))
		{
			Piece::Locations currentLocations = p.getCurrLocations();

			for (const Piece::Location& cl : currentLocations)
			{
				if (!isInYBounds(cl))
				{
					return PieceStatus::NoMoreRoom;
				}
			}

			for (const Piece::Location& cl : currentLocations)
			{
				bitmap[cl.y][cl.x] = true;
			}

			return PieceStatus::Settled;
		}
	}

	p.setNextLocation(locations[0]);
	return PieceStatus::Falling;
}

void Field::eraseCompleteRows()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		bool rowIsallTrue = std::accumulate(bitmap[y].begin(), bitmap[y].end(), true,
			[](bool acc, bool value)
			{ 
				return acc && value; 
			});

		if (rowIsallTrue)
		{
			collapseRow(y);
			renderTillY(y);
		}
	}
}
