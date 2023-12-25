#pragma once
#include "piece.h"
#include <array>

using PieceOffsets = const std::array<Location, 3>;
using PieceOrientations = const std::array<PieceOffsets, (size_t)PieceOrientation::NumberOfOrientation>;
using Pieces = const std::array<PieceOrientations, (size_t)PieceType::NumberOfPieces>;

extern Pieces piecesData;
