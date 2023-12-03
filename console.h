#pragma once

constexpr int FRAME_PERIOD_MS = 100;
constexpr int FALL_FACTOR = 10;

class Console
{
private:
	Console();
	Console(const Console&) = delete;
	Console& operator=(const Console&) = delete;

public:
	static Console& getInstance();
	void showCursor(bool showFlag);
	void setCursorPosition(char x, char y);
};
