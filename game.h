#pragma once

#include<array>

#include "piece.h"
#include "field.h"

/**
 * @brief: Singleton class managing the gameplay frame by frame 
 */
class Game
{
private:
	/**
	 * @brief enumeration of all commands in the game  
	 */
	enum class Direction
	{
		None,
		Left,
		Right,
		Down,
		Rotate,
	};

	Piece piece;		 // the falling piece
	Direction direction; // holds the commands currently pending
	Field field;		 // manages the field of the game

	/**
	 * @brief Private constructor to prevent instantiation from outside
	 */
	Game();

	/**
	 * @brief Delete the copy constructor 
	 */
	Game(const Game&) = delete;

	/**
	 * @brief Delete the assignment operator 
	 */
	Game& operator=(const Game&) = delete;

public:

	/**
	 * @brief get the signleton instance of this class
	 * 
	 * @return reference to the single instance of the game
	 */
	static Game& getInstance();

	/**
	 * @brief processes the next frame of the game
	 * 
	 * @return false if the game is over. Otherwise, true.
	 */
	bool tick();

	/**
	 * @brief set pending command to Up 
	 */
	void goUp();
	
	/**
	 * @brief set pending command to Left
	 */
	void goLeft();
	
	/**
	 * @brief set pending command to right
	 */
	void goRight();
	
	/**
	 * @brief set pending command to Down
	 */
	void goDown();
};
