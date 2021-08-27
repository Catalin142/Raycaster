#include "Core/RaycastPCH.h"

#include "Win32Window.h"
#include "ScreenBuffer.h"

#include "Events/EventDispatcher.h"
#include "Events/MouseEvents.h"

#include "Utils/Input.h"

Window* Window::m_Instance = nullptr;

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
	{
		auto window = Window::Get();
		window->m_Width = LOWORD(lParam);
		window->m_Height = HIWORD(lParam);

	} break;

	case WM_LBUTTONDOWN:
	{
		vec2 pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		MousePressedEvent ev(VK_MOUSE_LEFT, pt.x, pt.y);
		EventDispatcher::Dispatch(ev);
	} break;

	case WM_RBUTTONDOWN:
	{
		vec2 pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		MousePressedEvent ev(VK_MOUSE_RIGHT, pt.x, pt.y);
		EventDispatcher::Dispatch(ev);
	} break;

	case WM_LBUTTONUP:
	{
		vec2 pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		MouseReleasedEvent ev(VK_MOUSE_LEFT, pt.x, pt.y);
		EventDispatcher::Dispatch(ev);
	} break;

	case WM_RBUTTONUP:
	{
		vec2 pt;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		MouseReleasedEvent ev(VK_MOUSE_RIGHT, pt.x, pt.y);
		EventDispatcher::Dispatch(ev);
	} break;

	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
	} break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	} break;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Window::Window(const wchar_t* name, uint16 width, uint16 height, unsigned long flags) : m_Name(const_cast<wchar_t*>(name)), m_Width(width), m_Height(height), m_isRunning(true)
{
	//ShowCursor(false);
	m_Instance = this;
	
	m_WindowClass = { };

	HINSTANCE hInstance = GetModuleHandle(NULL);

	m_WindowClass.lpfnWndProc = WindowProcedure;
	m_WindowClass.hInstance = GetModuleHandle(NULL);
	m_WindowClass.lpszClassName = L"Odium Class";

	RegisterClass(&m_WindowClass);

	m_WindowHandle = CreateWindowEx(0, L"Odium Class", m_Name, flags,
		CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height,
		NULL, NULL, hInstance, NULL);

	if (!m_WindowHandle)
	{
		std::cout << "Nu s-a putut creea fereastra" << std::endl;
		assert(m_WindowHandle);
	}

	m_DeviceContext = GetDC(m_WindowHandle);

	RECT r;
	GetWindowRect(m_WindowHandle, &r);
	ClipCursor(&r);

	ShowWindow(m_WindowHandle, SW_SHOW);
}

void Window::pollEvents()
{
	MSG msg = { };
 	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

	if (msg.message == WM_QUIT)
	{
		m_isRunning = false;
	}

	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

vec2 Window::getClientRectSize()
{
	RECT rct;
	GetClientRect(Window::Get()->getHandle(), &rct);
	return { (float)rct.right, (float)rct.bottom };
}
