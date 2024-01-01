#pragma once
#include <array>
#include "piece.h"


/**
 * @brief generates and stores the piece block offsets statically 
 */
class Pieces
{
private:
	// array type for one piece offsets
	using Offsets = const std::array<Piece::Location, 3>;
	// array type for one piece orientation
	using Orientations = std::array<Offsets, (size_t)Piece::Orientation::NumberOfOrientation>;
	// type for data array holding all pieces with their orientations and offsets
	using Data = const std::array<Orientations, (size_t)Piece::Type::NumberOfPieces>;

	// piece offsets static definitions
	static constexpr Offsets pieceO = { Piece::Location{ 1, 0 }, Piece::Location{ 0,-1 }, Piece::Location{ 1,-1 } };
	static constexpr Offsets pieceI = { Piece::Location{ 0,-1 }, Piece::Location{ 0,-2 }, Piece::Location{ 0,-3 } };
	static constexpr Offsets pieceS = { Piece::Location{ 1, 0 }, Piece::Location{ 1,-1 }, Piece::Location{ 2,-1 } };
	static constexpr Offsets pieceZ = { Piece::Location{-1, 0 }, Piece::Location{-1,-1 }, Piece::Location{-2,-1 } };
	static constexpr Offsets pieceL = { Piece::Location{-1, 0 }, Piece::Location{-1,-1 }, Piece::Location{-1,-2 } };
	static constexpr Offsets pieceJ = { Piece::Location{ 1, 0 }, Piece::Location{ 1,-1 }, Piece::Location{ 1,-2 } };
	static constexpr Offsets pieceT = { Piece::Location{ 0,-1 }, Piece::Location{-1,-1 }, Piece::Location{ 1,-1 } };
	
	/**
	 * @brief rotate location to a given orientation
	 * 
	 * @param l location to rotate
	 * @param o desired orientation
	 * 
	 * @return rotated location
	 */
	constexpr Piece::Location rotateLocation(Piece::Location l, Piece::Orientation o);
	
	/**
	 * @brief rotate offsets to a given orientation
	 * 
	 * @param f offsets to rotate
	 * @param o desired orientation
	 * 
	 * @return rotated offsets
	 */
	constexpr Offsets rotateOffsets(Offsets f, Piece::Orientation o);

	/**
	 * @brief from offsets generate all possible orientations
	 *
	 * @param f		starting offsets
	 * @param o0	desired orientation at 0 degrees
	 * @param o90	desired orientation at 90 degrees
	 * @param o180	desired orientation at 180 degrees
	 * @param o270	desired orientation at 270 degrees
	 * 
	 * @return generated orientations
	 */
	constexpr Orientations generateOrientations(Offsets f, Piece::Orientation o0, Piece::Orientation o90, Piece::Orientation o180, Piece::Orientation o270);
	
	/**
	 * @brief populates the data of this class statically
	 * 
	 * @returns generated offset data for all pieces in all orientations
	 */
	constexpr Data generateData();

	/**
	 * @brief populates data
	 */
	Pieces();

	Data data; // offset data for all pieces in all orientations

public:

	/**
	 * @brief getter for the single pieces instance
	 * 
	 * @return references to the single instance
	 */
	static Pieces& getInstance();

	/**
	 * @brief getter for data
	 *
	 * @return reference to data
	 */
	Data& getData();
};
