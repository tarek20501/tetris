#include "pieces_data.h"

constexpr Location rotateLocation(Location l, PieceOrientation o)
{
	for (int i = 0; i < (int)o; i++)
	{
		int rotatedOffsetX = l.x;
		l.x = -l.y;
		l.y = rotatedOffsetX;
	}
	return l;
}

constexpr PieceOffsets rotateOffsets(PieceOffsets f, PieceOrientation o)
{
	return
	{
		rotateLocation(f[0], o),
		rotateLocation(f[1], o),
		rotateLocation(f[2], o),
	};
}

constexpr PieceOrientations generateOrientations(PieceOffsets f, PieceOrientation o0, PieceOrientation o90, PieceOrientation o180, PieceOrientation o270)
{
	return PieceOrientations
	{
		rotateOffsets(f, o0),
		rotateOffsets(f, o90),
		rotateOffsets(f, o180),
		rotateOffsets(f, o270),
	};
}

constexpr PieceOffsets pieceO = { Location{ 1, 0 }, Location{ 0,-1 }, Location{ 1,-1 } };
constexpr PieceOffsets pieceI = { Location{ 0,-1 }, Location{ 0,-2 }, Location{ 0,-3 } };
constexpr PieceOffsets pieceS = { Location{ 1, 0 }, Location{ 1,-1 }, Location{ 2,-1 } };
constexpr PieceOffsets pieceZ = { Location{-1, 0 }, Location{-1,-1 }, Location{-2,-1 } };
constexpr PieceOffsets pieceL = { Location{-1, 0 }, Location{-1,-1 }, Location{-1,-2 } };
constexpr PieceOffsets pieceJ = { Location{ 1, 0 }, Location{ 1,-1 }, Location{ 1,-2 } };
constexpr PieceOffsets pieceT = { Location{ 0,-1 }, Location{-1,-1 }, Location{ 1,-1 } };

constexpr Pieces piecesData
{
	generateOrientations(pieceO, PieceOrientation::O0, PieceOrientation::O0, PieceOrientation::O0, PieceOrientation::O0),
	generateOrientations(pieceI, PieceOrientation::O0, PieceOrientation::O90, PieceOrientation::O0, PieceOrientation::O90),
	generateOrientations(pieceS, PieceOrientation::O0, PieceOrientation::O90, PieceOrientation::O180, PieceOrientation::O270),
	generateOrientations(pieceZ, PieceOrientation::O0, PieceOrientation::O90, PieceOrientation::O180, PieceOrientation::O270),
	generateOrientations(pieceL, PieceOrientation::O0, PieceOrientation::O90, PieceOrientation::O180, PieceOrientation::O270),
	generateOrientations(pieceJ, PieceOrientation::O0, PieceOrientation::O90, PieceOrientation::O180, PieceOrientation::O270),
	generateOrientations(pieceT, PieceOrientation::O0, PieceOrientation::O90, PieceOrientation::O180, PieceOrientation::O270)
};
