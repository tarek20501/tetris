#pragma once

/**
 * @brief: Singleton class managing the game play by frame 
 */
class Game
{
public:

	/**
	 * @brief: get the signleton instance of this class
	 */
	static Game& getInstance();

	/**
	 * @brief: processes the next frame of the game
	 */
	void tick();

private:

	// Private constructor to prevent instantiation from outside
	Game();

	// Delete the copy constructor
	Game(const Game&) = delete;

	// Delete the assignment operator
	Game& operator=(const Game&) = delete;
};
