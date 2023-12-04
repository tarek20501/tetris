#pragma once

#include <array>

constexpr int FRAME_PERIOD_MS = 100;
constexpr int FALL_FACTOR = 10;
constexpr unsigned int WIDTH = 20;
constexpr unsigned int HEIGHT = 20;
using BitMap = std::array<std::array<bool, WIDTH>, HEIGHT>;

class Console
{
private:
	BitMap bitMap;

	Console();
	Console(const Console&) = delete;
	Console& operator=(const Console&) = delete;
	static void showCursor(bool showFlag);
	static void setCursorPositionRaw(char x, char y);
	static void setCursorPositionBitMap(int x, int y);
	static void intializeWindow();

public:
	static Console& getInstance();
	void renderNextFrame(BitMap& nextBitMap);
};
