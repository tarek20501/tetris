#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <conio.h> // @FIXME Windows specific library

#include "game.h"

using namespace std;

condition_variable cv;      // condition variable to signal the main thread
mutex m;                    // mutex to protect the shared data
bool alive = true;          // game is running

/**
 * @brief A function to handle the timer event
 *
 * @param interval for notifying the main thread in milliseconds
 */
void timerThread(int interval)
{
    while (alive)
    {
        this_thread::sleep_for(chrono::milliseconds(interval));

        lock_guard<mutex> lock(m);

        cv.notify_one();
    }
}

/**
 * @brief A function to handle the key press event
 */ 
void keyboardThread()
{
    Game& game = Game::getInstance();
    while (alive)
    {
        constexpr int UP_ARROW = 72;
        constexpr int LEFT_ARROW = 75;
        constexpr int RIGHT_ARROW = 77;
        constexpr int DOWN_ARROW = 80;
        constexpr int ESC_KEY = 27;
        unsigned char ch = _getch(); // get a character from the keyboard

        // if the first value is 0 or 224, then it is an arrow key
        if (ch == 0 || ch == 224)
        {
            ch = _getch();

            switch (ch)
            {
            case UP_ARROW:
                game.goUp();
                break;
            case LEFT_ARROW:
                game.goLeft();
                break;
            case RIGHT_ARROW:
                game.goRight();
                break;
            case DOWN_ARROW:
                game.goDown();
                break;
            default:
                break;
            }
        }
        else if (ch == ESC_KEY)
        {
            alive = false;
        }
    }
}

/**
 * @brief Main Function  
 */
int main()
{
    thread timer(timerThread, FRAME_PERIOD_MS);
    thread keyboard(keyboardThread);

    timer.detach();
    keyboard.detach();

    Game& game = Game::getInstance();

    while (alive)
    {
        unique_lock<mutex> lock(m);
        cv.wait(lock);

        if (!game.tick())
        {
            break;
        }
    }

    alive = false;

    if (timer.joinable())
    {
        timer.join();
    }

    if (keyboard.joinable())
    {
        keyboard.join();
    }
   
    return 0;
}
