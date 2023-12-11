#pragma once

#include "console.h"
#include "piece.h"

using BitMap = std::array<std::array<bool, WIDTH>, HEIGHT>;

enum class FieldPieceStatus
{
	Falling,
	Settled,
	NoMoreRoom,
};

class Field
{
private:
	BitMap bitmap;
	bool isInBounds(Location& l);
public:
	Field();
	void setPieceNextLocationLeft(Piece& p);
	void setPieceNextLocationRight(Piece& p);
	FieldPieceStatus setPieceNextLocationDown(Piece& p);
};
