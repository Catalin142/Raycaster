#pragma once
#include "ScreenBuffer.h"
#include "Win32Window.h"
#include "Renderer/Camera.h"

#include "Core/RaycastPCH.h"
#include "Utils/Types.h"

struct Time
{
	static float deltaTime;
};

class Application
{
public:
	Application(const wchar_t* title, uint32 width = 1600, uint32 height = 900, uint32 bufferWidth = 320, uint32 bufferHeight = 240);
	virtual ~Application() = default;
	
	virtual void onCreate() { }
	virtual void onUpdate(float deltaTime) { }

	void Run();
	void setCamera(int posx, int posy, float fov);

protected:
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<ScreenBuffer> m_Buffer;
	std::shared_ptr<Camera> m_Camera;
};