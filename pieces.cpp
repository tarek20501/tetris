#include "pieces.h"

constexpr Piece::Location Pieces::rotateLocation(Piece::Location l, Piece::Orientation o)
{
	for (int i = 0; i < (int)o; i++)
	{
		int rotatedOffsetX = l.x;
		l.x = -l.y;
		l.y = rotatedOffsetX;
	}
	return l;
}

constexpr Pieces::Offsets Pieces::rotateOffsets(Offsets f, Piece::Orientation o)
{
	return
	{
		rotateLocation(f[0], o),
		rotateLocation(f[1], o),
		rotateLocation(f[2], o),
	};
}

constexpr Pieces::Orientations Pieces::generateOrientations(Offsets f, Piece::Orientation o0, Piece::Orientation o90, Piece::Orientation o180, Piece::Orientation o270)
{
	return Orientations
	{
		rotateOffsets(f, o0),
		rotateOffsets(f, o90),
		rotateOffsets(f, o180),
		rotateOffsets(f, o270),
	};
}

constexpr Pieces::Data Pieces::generateData()
{
	return 
	{
		generateOrientations(pieceO, Piece::Orientation::O0, Piece::Orientation::O0,  Piece::Orientation::O0,   Piece::Orientation::O0),
		generateOrientations(pieceI, Piece::Orientation::O0, Piece::Orientation::O90, Piece::Orientation::O0,   Piece::Orientation::O90),
		generateOrientations(pieceS, Piece::Orientation::O0, Piece::Orientation::O90, Piece::Orientation::O180, Piece::Orientation::O270),
		generateOrientations(pieceZ, Piece::Orientation::O0, Piece::Orientation::O90, Piece::Orientation::O180, Piece::Orientation::O270),
		generateOrientations(pieceL, Piece::Orientation::O0, Piece::Orientation::O90, Piece::Orientation::O180, Piece::Orientation::O270),
		generateOrientations(pieceJ, Piece::Orientation::O0, Piece::Orientation::O90, Piece::Orientation::O180, Piece::Orientation::O270),
		generateOrientations(pieceT, Piece::Orientation::O0, Piece::Orientation::O90, Piece::Orientation::O180, Piece::Orientation::O270)
	};
}

Pieces::Pieces(): data(generateData())
{
}

Pieces& Pieces::getInstance()
{
	static Pieces singleton;
	return singleton;
}

Pieces::Data& Pieces::getData()
{
	return data;
}
