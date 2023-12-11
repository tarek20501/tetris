#pragma once

#include <array>

constexpr int FRAME_PERIOD_MS = 20;
constexpr int FALL_FACTOR = 50;
constexpr int WIDTH = 20;
constexpr int HEIGHT = 20;

class Console
{
private:
	Console();
	Console(const Console&) = delete;
	Console& operator=(const Console&) = delete;
	static void showCursor(bool showFlag);
	static void setCursorPositionRaw(char x, char y);
	static void setCursorPositionBitMap(int x, int y);
	static void intializeWindow();

public:
	static Console& getInstance();
	static void drawBlock(int x, int y);
	static void eraseBlock(int x, int y);
};
