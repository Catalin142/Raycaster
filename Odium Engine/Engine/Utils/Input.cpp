#include "Core/RaycastPCH.h"

#include "Input.h"
#include "System/Win32Window.h"
#include "System/Application.h"

vec2 getMousePosition()
{
	POINT p = { 0.0, 0.0 };
	GetCursorPos(&p);
	ScreenToClient(Window::Get()->getHandle(), &p);

	return vec2((float)p.x, (float)p.y);
}

vec2 WindowToBufferCoordonates(const vec2& vec)
{
	vec2 normalPos = vec;
	auto app = Application::Get();

	vec2 norm = { (float)app->m_Buffer->getWidth() / (float)app->m_Window->getWidth(), (float)app->m_Buffer->getHeight() / (float)app->m_Window->getHeight() };
	normalPos = normalPos * norm;

	normalPos.y = app->m_Buffer->getHeight() - normalPos.y;

	return normalPos;
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

void setCursorVisibility(bool cursor)
{
	ShowCursor(cursor);
}
