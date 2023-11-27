// tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <Windows.h>

#include "game.h"
#include "console.h"

using namespace std;

condition_variable cv;      // condition variable to signal the main thread
mutex m;                    // mutex to protect the shared data
bool event = false;         // event flag
char command;               // holds the last keypress
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
        event = true;

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
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Check if left arrow is pressed
            game.loadCommand('L');
        }
        else if (!(GetAsyncKeyState(VK_LEFT) & 0x8000)) { // Check if left arrow is released
            game.clearCommand('L');
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Check if right arrow is pressed
            game.loadCommand('R');
        }
        else if (!(GetAsyncKeyState(VK_RIGHT) & 0x8000)) { // Check if right arrow is released
            game.clearCommand('R');
        }
        
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            alive = false;
        }

        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

int main()
{
    // Create a thread for the timer event
    thread timer(timerThread, 50);

    // Create a thread for the key press event
    thread keyboard(keyboardThread);

    // Detach the threads
    timer.detach();
    keyboard.detach();

    Console::showCursor(false);
    Game& game = Game::getInstance();

    // Main loop
    while (alive)
    {
        // Wait for a notification from the condition variable
        unique_lock<mutex> lock(m);
        cv.wait(lock);

        // Check the event flag and handle accordingly
        if (event)
        {
            game.tick();
        }

        // Reset the event flag
        event = false;
    }

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
