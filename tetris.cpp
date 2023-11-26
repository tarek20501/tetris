// tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <thread>
#include <chrono>
#include <iostream>
#include "game.h"
#include <condition_variable>
#include <Windows.h>

std::condition_variable cv;
std::mutex m;

void timer_start(unsigned int interval) {
    std::thread([interval]()
        {
            while (true)
            {
                cv.notify_one();
                std::this_thread::sleep_for(std::chrono::milliseconds(interval)); // Sleep for the interval
            }
        }).detach(); // Detach the thread
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
    ShowConsoleCursor(false);
    timer_start(500); // Start a timer that sets the flag every 1000 milliseconds
    std::unique_lock<std::mutex> lock(m);

    while (true)
    {
        cv.wait(lock);
        Game::getInstance().tick();
    }
    return 0;
}
