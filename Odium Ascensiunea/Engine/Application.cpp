#include "Core/RaycastPCH.h"

#include "Win32Window.h"
#include "ScreenBuffer.h"
#include "Renderer/Renderer.h"
#include "Utils/Color.h"
#include "Renderer/Camera.h"
#include "Utils/Raycaster.h"
#include "Utils/Random.h"

#include "Application.h"


float Time::deltaTime = 0.0f;

Application::Application(const wchar_t* title, uint32 width, uint32 height, uint32 bufferWidth, uint32 bufferHeight) :
	m_Window(std::make_shared<Window>(title, width, height)),
	m_Buffer(std::make_shared<ScreenBuffer>(m_Window, bufferWidth, bufferHeight))
{ }

void Application::Run()
{
	std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> oldTime = timeNow;

	float lastFrameChange = 0.4f;

	onCreate();
	Renderer::Init(m_Buffer);
	Random::Init;

	while (m_Window->isRunning())
	{
		timeNow = std::chrono::system_clock::now();
		Time::deltaTime = std::chrono::duration<float>(timeNow - oldTime).count();

		m_Camera->onUpdate(Time::deltaTime);

		if (lastFrameChange >= 0.5f)
		{
			std::wstring title = m_Window->getName() + L": FPS " + std::to_wstring(int(1 / Time::deltaTime));
			SetWindowText(m_Window->getHandle(), title.c_str());
			lastFrameChange = 0.0f;
		}

		onUpdate(Time::deltaTime);

		lastFrameChange += Time::deltaTime;

		m_Buffer->Render();
		m_Window->pollEvents();


		if (GetAsyncKeyState(VK_ESCAPE))
			m_Window->isRunning() = false; // TODO scoatel

		oldTime = timeNow;
	}
}

void Application::setCamera(int posx, int posy, float fov)
{
	m_Camera = std::make_shared<Camera>(posx + 0.5f, posy + 0.5f, fov);
}
