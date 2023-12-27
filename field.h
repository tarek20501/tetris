#pragma once

#include <functional>
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
	Console& console;

	bool isInBounds(const Location& l);
	bool isInXBounds(const Location& l);
	bool isInYBounds(const Location& l);
	bool isInYPlayBounds(const Location& l);
	bool isCollision(const Location& l);
	void collapseRow(int y);
	void renderTillY(int y);

public:
	Field();
	void setPieceNextLocation(Piece& p, std::function<PieceLocations()> pieceLocationsMethod);
	void setPieceNextOrientation(Piece& p);
	FieldPieceStatus handleFalling(Piece& p);
	void eraseCompleteRows();
};
