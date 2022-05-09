#pragma once
#include <Windows.h>
#include "Utils/Types.h"
#include "Utils/Maths.h"

#include <functional>

class Window
{
friend LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	Window(const wchar_t* name, uint16 width, uint16 height, unsigned long flags = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX);

	void pollEvents();

	uint16 getWidth() { return m_Width; }
	uint16 getHeight() { return m_Height; }
	HWND& getHandle() { return m_WindowHandle; }
	HDC& getDeviceContext() { return m_DeviceContext; }

	void setWidth(uint16 width) { m_Width = width; }
	void setHeight(uint16 height) { m_Height = height; }
	vec2 getClientRectSize();

	bool& isRunning() { return m_isRunning; }
	std::wstring getName() { return std::wstring(m_Name); }

	static Window* Get() { return m_Instance; }

private:
	HWND m_WindowHandle;
	WNDCLASS m_WindowClass;
	HDC m_DeviceContext;

	uint16 m_Width;
	uint16 m_Height;
	vec2 m_ClientSize;

	wchar_t* m_Name;
	bool m_isRunning;

	static Window* m_Instance;
};