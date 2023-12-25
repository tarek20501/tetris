#include "piece.h"

using PieceOffsets = const std::array<Location, 3>;
using Pieces = const std::array<PieceOffsets, (size_t)PieceType::NumberOfPieces>;
using PiecesRotated = const std::array<Pieces, (size_t)PieceOrientation::NumberOfOrientation>;


const constexpr Location rotateOffset(Location offset, PieceOrientation o)
{
	for (int i = 0; i < (int)o; i++)
	{
		int rotatedOffsetX = offset.x;
		offset.x = -offset.y;
		offset.y = rotatedOffsetX;
	}
	return offset;
}

constexpr PieceOffsets rotatePiece(PieceOffsets f, PieceOrientation o)
{
	return
	{
		rotateOffset(f[0], o),
		rotateOffset(f[1], o),
		rotateOffset(f[2], o),
	};
}

constexpr Pieces rotatePieces(Pieces p, PieceOrientation o)
{
	return
	{
		rotatePiece(p[0], o),
		rotatePiece(p[1], o),
		rotatePiece(p[2], o),
		rotatePiece(p[3], o),
		rotatePiece(p[4], o),
		rotatePiece(p[5], o),
		rotatePiece(p[6], o),
	};
}

constexpr Pieces pieces =
{
	PieceOffsets{Location{ 1, 0 }, Location{ 0,-1 }, Location{ 1,-1 }}, // O
	PieceOffsets{Location{ 0,-1 }, Location{ 0,-2 }, Location{ 0,-3 }}, // I
	PieceOffsets{Location{ 1, 0 }, Location{ 1,-1 }, Location{ 2,-1 }}, // S
	PieceOffsets{Location{-1, 0 }, Location{-1,-1 }, Location{-2,-1 }}, // Z
	PieceOffsets{Location{-1, 0 }, Location{-1,-1 }, Location{-1,-2 }}, // L
	PieceOffsets{Location{ 1, 0 }, Location{ 1,-1 }, Location{ 1,-2 }}, // J
	PieceOffsets{Location{ 0,-1 }, Location{-1,-1 }, Location{ 1,-1 }}, // T
};

PiecesRotated piecesRotated =
{
	rotatePieces(pieces, PieceOrientation::O0),
	rotatePieces(pieces, PieceOrientation::O90),
	rotatePieces(pieces, PieceOrientation::O180),
	rotatePieces(pieces, PieceOrientation::O270),
};
