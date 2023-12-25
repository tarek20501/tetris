#pragma once

#include<array>

#include "console.h"
#include "piece.h"
#include "field.h"

enum class Direction
{
	Neither,
	Left,
	Right,
	Down,
	Rotate,
};

/**
 * @brief: Singleton class managing the game play by frame 
 */
class Game
{
private:
	Piece piece;
	Direction direction;
	Field field;

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
	bool tick();

	void goUp();
	void goLeft();
	void goRight();
	void goDown();
};
