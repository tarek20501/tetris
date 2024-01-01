#pragma once

#include <random>
#include <array>
#include "console.h"

/**
 * @brief keeps track of the locations of the blocks making the falling piece
 */
class Piece
{
public:
	/**
	 * @brief x and y coordinates for block location 
	 */
	struct Location
	{
		int x; // x-coordiate
		int y; // y-coordiate

		/**
		 * @brief Add two locations
		 * 
		 * @param other location to add
		 * 
		 * @return the resulting location
		 */
		Location operator+(Location other);
	};

	/**
	 * @brief enumeration of all pieces that could possibly fall 
	 */
	enum class Type
	{
		O,
		I,
		S,
		Z,
		L,
		J,
		T,
		NumberOfPieces
	};

	/**
	 * @brief enumeration of all possible piece orientations 
	 */
	enum class Orientation
	{
		O0 = 0,
		O90,
		O180,
		O270,
		NumberOfOrientation
	};

	// array type for all locations of blocks making up one piece  
	using Locations = const std::array<Location, 4>;

private:
	Location currLocation; // current piece location
	Location nextLocation; // next piece location
	Type type; // type of currently falling piece
	Orientation currOrientation; // current piece orientation
	Orientation nextOrientation; // next piece orientation
	Console& console; // reference to user interface
	std::default_random_engine engine; // random number generator
	std::uniform_int_distribution<int> typeDistribution; // random numbers distribution for piece type
	std::uniform_int_distribution<int> orientationDistribution; // random numbers distribution for piece orientation

	/**
	 * @brief Given a location and orientation calculate the locations of blocks making up the currently falling piece
	 * 
	 * @param l reference to location
	 * @param o orientation
	 * 
	 * @return array of locations making up the piece
	 */
	Locations calculatePieceLocations(Location& l, Orientation o);

	/**
	 * @brief erase this piece from given location and orientation
	 *
	 * @param l location
	 * @param o orientation
	 */
	void erasePiece(Location& l, Orientation& o);

	/**
	 * @brief draw this piece on given location and orientation
	 *
	 * @param l location
	 * @param o orientation
	 */
	void drawPiece(Location& l, Orientation& o);

	/**
	 * initialize member variabes
	 */
	Piece();

public:

	/**
	 * @brief Getter for the signle piece instance
	 *
	 * @return reference to the single piece instance
	 */
	static Piece& getInstance();

	/**
	 * @brief respawn a new piece 
	 */
	void reset();

	/**
	 * @brief if the piece moved to the right, get the locations of the blocks
	 *
	 * @return array for locations of blocks
	 */
	Locations getNextRightLocations();
	
	/**
	 * @brief if the piece moved to the left, get the locations of the blocks
	 *
	 * @return array for locations of blocks
	 */
	Locations getNextLeftLocations();

	/**
	 * @brief if the piece moved down, get the locations of the blocks
	 *
	 * @return array for locations of blocks
	 */
	Locations getNextDownLocations();

	/**
	 * @brief if the piece rotated clockwise, get the locations of the blocks
	 *
	 * @return array for locations of blocks
	 */
	Locations getNextOrientationLocations();

	/**
	 * @brief setter for the piece's next location
	 * 
	 * @param l next location
	 */
	void setNextLocation(Location l);

	/**
	 * @brief set piece's next orientation to the next one in clockwise direction
	 */
	void setNextOrientation();

	/**
	 * @brief get locations of blocks the piece currently occupying
	 *
	 * @return array for locations of blocks
	 */
	Locations getCurrLocations();

	/**
	 * @brief move the piece from current location/orientation to next location/orientation on the UI
	 */
	void move();
};

/**
 * @brief cycle through Piece::Orientation enum
 * 
 * @param po piece oriention to operate on
 * 
 * @return the next orientation in the cycle
 */
Piece::Orientation operator++(Piece::Orientation& po, int);
