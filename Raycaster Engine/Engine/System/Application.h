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
	friend class Input;

public:
	Application(const wchar_t* title, uint32 width = 1600, uint32 height = 900, uint32 bufferWidth = 320, uint32 bufferHeight = 200);
	virtual ~Application();
	
	void pushLayer(Layer* layer);
	void pushOverlay(Layer* layer);

	void popLayer();
	void popOverlay();

	void Run();

	std::shared_ptr<Window>& getWindow() { return m_Window; }
	std::shared_ptr<ScreenBuffer>& getBuffer() { return m_Buffer; }

	static Application* Get() { return m_Instance; }

protected:
	std::shared_ptr<Window> m_Window;
	std::shared_ptr<ScreenBuffer> m_Buffer;

	std::vector<Layer*> m_Layers;
	int m_NoOfLayers = 0;

	static Application* m_Instance;
};