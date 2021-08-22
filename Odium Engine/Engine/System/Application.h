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
	friend class Layer;
	friend class Entity;

public:
	Application(const wchar_t* title, uint32 width = 1600, uint32 height = 900, uint32 bufferWidth = 320, uint32 bufferHeight = 200);
	virtual ~Application() = default;
	
	void setLayer(Layer* layer);

	void Run();
	void setCamera(int posx, int posy, float fov);

	static Application* Get() { return m_Instance; }

protected:
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<ScreenBuffer> m_Buffer;
	std::shared_ptr<Camera> m_Camera;

	Layer* m_CurrentLayer = nullptr;

	static Application* m_Instance;
};