#pragma once

/**
 * @brief Front End API
 */
class Console
{
private:
	constexpr static int X_OFFSET = 1; // Offset for x coordinates
	constexpr static int X_FACTOR = 2; // factor to multiply x coordinate

	/**
	 * @brief initialize user interface
	 */
	Console();

	/**
	 * @brief delete copy constructor 
	 */
	Console(const Console&) = delete;
	
	/**
	 * @brief delete assignment constructor
	 */
	Console& operator=(const Console&) = delete;

	/**
	 * @brief show/hide console cursor 
	 * 
	 * @param showFlag true to show 
	 *                 false to hide
	 */
	static void showCursor(bool showFlag);

	/**
	 * @brief set console position at x and y in raw console coordinates
	 * 
	 * @param x raw console coordinate
	 * @param y raw console coordinate
	 */
	static void setCursorPositionRaw(char x, char y);

	/**
	 * @brief set console position at x and y in bitmap coordinates
	 *
	 * @param x bitmap coordinate
	 * @param y bitmap coordinate
	 */
	static void setCursorPositionBitMap(int x, int y);

	/**
	 * @brief setup console window 
	 */
	static void intializeWindow();

public:

	/**
	 * @brief Getter for the single console instance
	 *
	 * @return the single console instance
	 */
	static Console& getInstance();

	/**
	 * @brief Draw a block at bitmap coordinates x and y
	 *
	 * @param x coordinate
	 * @param y coordinate
	 */
	static void drawBlock(int x, int y);

	/**
	 * @brief Erase a block at bitmap coordinates x and y
	 *
	 * @param x coordinate
	 * @param y coordinate
	 */
	static void eraseBlock(int x, int y);
};
