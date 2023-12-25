// tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <Windows.h>
#include <conio.h>

#include "game.h"
#include "console.h"

using namespace std;

condition_variable cv;      // condition variable to signal the main thread
mutex m;                    // mutex to protect the shared data
bool alive = true;          // game is running

// A function to handle the timer event
void timerThread(int interval)
{
    while (alive)
    {
        // Sleep for the specified interval
        this_thread::sleep_for(chrono::milliseconds(interval));

        // Lock the mutex and set the event flag to 1
        lock_guard<mutex> lock(m);

        // Notify the main thread
        cv.notify_one();
    }
}

// A function to handle the key press event
void keyboardThread()
{
    Game& game = Game::getInstance();
    while (alive)
    {
        const int UP_ARROW = 72;
        const int LEFT_ARROW = 75;
        const int RIGHT_ARROW = 77;
        const int DOWN_ARROW = 80;
        unsigned char ch = _getch(); // get a character from the keyboard

        if (ch == 0 || ch == 224) // if the first value is 0 or 224, then it is an arrow key
        {
            ch = _getch(); // get the second value of the arrow key

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
        else if (ch == 27) // if the character is ESC, then exit the loop
        {
            alive = false;
        }
    }
}

int main()
{
    // Create a thread for the timer event
    thread timer(timerThread, FRAME_PERIOD_MS);

    // Create a thread for the key press event
    thread keyboard(keyboardThread);

    // Detach the threads
    timer.detach();
    keyboard.detach();

    Game& game = Game::getInstance();

    // Main loop
    while (alive)
    {
        // Wait for a notification from the condition variable
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
