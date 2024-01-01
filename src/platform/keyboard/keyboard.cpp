#include <conio.h>

#include "keyboard.h"
#include "game.h"

void keyboardThread()
{
    extern bool alive;
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
