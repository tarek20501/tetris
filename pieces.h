#pragma once
#include <array>
#include "piece.h"


class Pieces
{
private:
	using Offsets = const std::array<Piece::Location, 3>;
	using Orientations = std::array<Offsets, (size_t)Piece::Orientation::NumberOfOrientation>;
	using Data = const std::array<Orientations, (size_t)Piece::Type::NumberOfPieces>;

	static constexpr Offsets pieceO = { Piece::Location{ 1, 0 }, Piece::Location{ 0,-1 }, Piece::Location{ 1,-1 } };
	static constexpr Offsets pieceI = { Piece::Location{ 0,-1 }, Piece::Location{ 0,-2 }, Piece::Location{ 0,-3 } };
	static constexpr Offsets pieceS = { Piece::Location{ 1, 0 }, Piece::Location{ 1,-1 }, Piece::Location{ 2,-1 } };
	static constexpr Offsets pieceZ = { Piece::Location{-1, 0 }, Piece::Location{-1,-1 }, Piece::Location{-2,-1 } };
	static constexpr Offsets pieceL = { Piece::Location{-1, 0 }, Piece::Location{-1,-1 }, Piece::Location{-1,-2 } };
	static constexpr Offsets pieceJ = { Piece::Location{ 1, 0 }, Piece::Location{ 1,-1 }, Piece::Location{ 1,-2 } };
	static constexpr Offsets pieceT = { Piece::Location{ 0,-1 }, Piece::Location{-1,-1 }, Piece::Location{ 1,-1 } };

	constexpr Piece::Location rotateLocation(Piece::Location l, Piece::Orientation o);
	constexpr Offsets rotateOffsets(Offsets f, Piece::Orientation o);
	constexpr Orientations generateOrientations(Offsets f, Piece::Orientation o0, Piece::Orientation o90, Piece::Orientation o180, Piece::Orientation o270);
	constexpr Data generateData();

	Pieces();
	Data data;

public:
	static Pieces& getInstance();
	Data& getData();
};
