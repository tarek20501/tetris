#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

#include "keyboard.h"
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
