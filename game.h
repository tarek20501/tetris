#pragma once

/**
 * @brief: Singleton class managing the game play by frame 
 */
class Game
{
private:
	char command;

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

	/**
	 * @brief: load command to be executed in the next frame  
	 */
	void loadCommand(const char c);

	/**
	 * @brief: clear command
	 */
	void clearCommand(const char c);
};
