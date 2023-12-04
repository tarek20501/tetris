#pragma once

#include<array>

#include "console.h"

enum class Direction
{
	Neither,
	Left,
	Right
};

struct Location
{
	int x;
	int y;
};

/**
 * @brief: Singleton class managing the game play by frame 
 */
class Game
{
private:
	Console& console;
	Direction direction;
	Location location;
	BitMap bitMap;

	/**
	 * @brief: Private constructor to prevent instantiation from outside
	 */
	Game();

	Game(const Game&) = delete; // Delete the copy constructor

	Game& operator=(const Game&) = delete; // Delete the assignment operator

public:

	/**
	 * @brief: get the signleton instance of this class
	 */
	static Game& getInstance();

	/**
	 * @brief: processes the next frame of the game
	 */
	void tick();

	void goLeft();
	void goRight();
};
