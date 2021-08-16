#include "Core/RaycastPCH.h"

#include "Input.h"
#include "Win32Window.h"

vec2 getMousePosition()
{
	POINT p = { 0.0f, 0.0f };
	GetCursorPos(&p);
	ScreenToClient(Window::Get()->getHandle(), &p);

	return vec2(p.x, p.y);
}

void setMousePosition(int x, int y)
{
	SetCursorPos(x, y);
}

void pinMouse()
{
	RECT rct;
	GetClientRect(Window::Get()->getHandle(), &rct);

	POINT pt = { rct.right / 2, rct.bottom / 2 };
	ClientToScreen(Window::Get()->getHandle(), &pt);

	setMousePosition(pt.x, pt.y);
}
