#include <iostream>
#include <Windows.h>

#include "tetris.h"
#include "console.h"

void Console::intializeWindow()
{
    // Get the handle to the console output buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Create a SMALL_RECT structure that specifies the new window size
    SMALL_RECT windowSize = { 0, 0, WIDTH * X_FACTOR + X_OFFSET * 2, HEIGHT + 1};

    // Set the console window size using the structure
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Get the window handle of the console window
    HWND hWnd = GetConsoleWindow();

    // Get the current window style
    LONG style = GetWindowLong(hWnd, GWL_STYLE);

    // Remove the WS_THICKFRAME and WS_VSCROLL flags from the style
    style &= ~(WS_THICKFRAME | WS_VSCROLL);

    // Set the new window style
    SetWindowLong(hWnd, GWL_STYLE, style);

    // Get the handle to the console input buffer
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    // Get the current console mode
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);

    // Disable the quick-edit mode using the ENABLE_EXTENDED_FLAGS flag
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    // Set the console screen buffer size to match the window size
    COORD coord = {};
    coord.X = windowSize.Right + 1;
    coord.Y = windowSize.Bottom + 1;
    SetConsoleScreenBufferSize(hConsole, coord);
}

Console::Console()
{
    intializeWindow();
    showCursor(false);
    for (int y = 0; y < HEIGHT; y++)
    {
        std::cout << "<!";
        for (int x = 0; x < WIDTH; x++)
        {
            std::cout << " .";
        }
        std::cout << "!>" << std::endl;
    }
    std::cout << "<!";
    for (int x = 0; x < WIDTH; x++)
    {
        std::cout << "==";
    }
    std::cout << "!>" << std::endl;
    
    std::cout << "  ";
    for (int x = 0; x < WIDTH; x++)
    {
        std::cout << "\\/";
    }
    std::cout << "  ";
}

Console& Console::getInstance()
{
    static Console console;
    return console;
}

void Console::showCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Console::setCursorPositionRaw(char x, char y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void Console::setCursorPositionBitMap(int x, int y)
{
    x = x * X_FACTOR + X_OFFSET;
    setCursorPositionRaw(x, y);
}

void Console::drawBlock(int x, int y)
{
    if (x < 0 || x >= WIDTH)
    {
        return;
    }
    if (y < 0 || y >= HEIGHT)
    {
        return;
    }
    setCursorPositionBitMap(x, y);
    std::cout << "[]";
}

void Console::eraseBlock(int x, int y)
{
    if (x < 0 || x >= WIDTH)
    {
        return;
    }
    if (y < 0 || y >= HEIGHT)
    {
        return;
    }
    setCursorPositionBitMap(x, y);
    std::cout << " .";
}
