#pragma once
#include "Maths.h"

class Input
{
public:
	static bool isPressed(int code);
	static void blockInput(bool b) { m_BlockInput = b; }

	static vec2 getMousePosition();

	static void setMousePosition(int x, int y);
	static void showCursor(bool cursor);

	static void pinMouse(bool status);

	static vec2 WindowToBufferCoordonates(const vec2& vec);

private:
	static bool m_BlockInput;

private:
	Input() = default;
	~Input() = default;
};

#define VK_MOUSE_LEFT 1
#define VK_MOUSE_RIGHT 2
#define VK_MOUSE_MIDDLE 3
