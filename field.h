#pragma once

#include <functional>
#include <array>

#include "tetris.h"
#include "console.h"
#include "piece.h"

/**
 * @brief Singleton class to manage the blocks making up the field of the game
 */
class Field
{
private:
	using BitMap = std::array<std::array<bool, WIDTH>, HEIGHT>;

public:
	/**
	 * status of the falling piece
	 */
	enum class PieceStatus
	{
		Falling,
		Settled,
		NoMoreRoom,
	};

private:
	BitMap bitmap;		// keeps track of which blocks are occupied
	Console& console;	// User interface API

	/**
	 * @brief check whether given location is in bitmap x and y bounds
	 * 
	 * @param l location to check
	 * 
	 * @return true if within bounds
	 */
	bool isInBounds(const Location& l);

	/**
	 * @brief check whether given location is in bitmap x bounds
	 *
	 * @param l location to check
	 *
	 * @return true if within bounds
	 */
	bool isInXBounds(const Location& l);

	/**
	 * @brief check whether given location is in bitmap y bounds
	 *
	 * @param l location to check
	 *
	 * @return true if within bounds
	 */
	bool isInYBounds(const Location& l);

	/**
	 * @brief check whether given location is in bitmap y playable bounds
	 *
	 * @param l location to check
	 *
	 * @return true if within playable bounds
	 */
	bool isInYPlayBounds(const Location& l);

	/**
	 * @brief check whether given location is an occupied block
	 *
	 * @param l location to check
	 *
	 * @return true if block at location is occupied
	 */
	bool isCollision(const Location& l);

	/**
	 * @brief delete row at y and shift the upper rows down by one
	 * 
	 * @param y index of row to collapse
	 */
	void collapseRow(int y);

	/**
	 * @brief refresh the UI by rendering the bitmap fro row 0 until y
	 * 
	 * @param y index of the last row to render 
	 */
	void renderTillY(int y);

public:
	/**
	 * @brief initialize bitmap and UI
	 */
	Field();

	/**
	 * @brief get piece next location using pieceLocationsMethod
	 *        if this next location doesn't cause a collision with
	 *        an occupied block or going out of game bounds
	 *        then set the piece next location. Otherwise, don't.
	 * 
	 * @param p reference to piece to set its next location
	 * @param pieceLocationsMethod method to get next locations requested by game
	 */
	void setPieceNextLocation(Piece& p, std::function<PieceLocations()> pieceLocationsMethod);

	/**
	 * @brief get piece next locations in the next orientation
	 *        if this next location doesn't cause a collision with
	 *        an occupied block or going out of game bounds
	 *        then set the piece next orientation. Otherwise, don't.
	 *
	 * @param p reference to piece to set its next orientation
	 */
	void setPieceNextOrientation(Piece& p);

	/**
	 * @brief Decide if given piece is allowed to fall
	 *        if so set its next location down
	 *        if not let it settle in the bitmap
	 *        check if the game is over
	 * 
	 * @param p reference to piece
	 * 
	 * @return PieceStatus
	 */
	PieceStatus handleFalling(Piece& p);

	/**
	 * @brief scan the bitmap for completely occupied rows
	 *        if a complete one is found, collapse it
	 *        refresh the UI
	 */
	void eraseCompleteRows();
};
