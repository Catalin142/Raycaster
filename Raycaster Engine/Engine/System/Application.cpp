#include "Core/RaycastPCH.h"

#include "Win32Window.h"
#include "ScreenBuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/WorldRenderer.h"
#include "Utils/Color.h"
#include "Renderer/Camera.h"
#include "Utils/Raycaster.h"
#include "Utils/Random.h"
#include "Layer.h"
#include "Tools/Benchmark.h"

#include "Application.h"

Application* Application::m_Instance;
float Time::deltaTime = 0.0f;

Application::Application(const wchar_t* title, uint32 width, uint32 height, uint32 bufferWidth, uint32 bufferHeight) :
	m_Window(std::make_shared<Window>(title, width, height)),
	m_Buffer(std::make_shared<ScreenBuffer>(m_Window, bufferWidth, bufferHeight))
{
	START_SCOPE_PROFILE("Init");
	m_Instance = this;

	Font::Init("Resources/Font.spr", "Resources/Numbers.spr", "Resources/Symbols.spr", 6, 7);
	WorldRenderer::Init();
	Random::Init();
}

Application::~Application()
{
	WorldRenderer::Destroy();
}

void Application::pushLayer(Layer* layer)
{
	m_Layers.emplace_back(layer);
	m_NoOfLayers++;
	layer->onAttach();
}

void Application::pushOverlay(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_NoOfLayers, layer);
	layer->onAttach();
}

void Application::popLayer()
{
	auto lastLayer = m_Layers.begin() + m_NoOfLayers;
	(*lastLayer)->onDetach();
	m_NoOfLayers--;
	m_Layers.erase(lastLayer);
}

void Application::popOverlay()
{
	if (m_Layers.size() > m_NoOfLayers)
	{
		m_Layers.back()->onDetach();
		m_Layers.pop_back();
	}
}

void Application::Run()
{
	std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> oldTime = timeNow;

	float lastFrameChange = 0.4f;

	Renderer::Init(m_Buffer);
	Random::Init();

	while (m_Window->isRunning())
	{
		START_SCOPE_PROFILE("Main loop");
		m_Buffer->ClearDepthBuffer();

		timeNow = std::chrono::system_clock::now();
		Time::deltaTime = std::chrono::duration<float>(timeNow - oldTime).count();

		if (lastFrameChange >= 0.5f)
		{
			std::wstring title = m_Window->getName() + L": FPS " + std::to_wstring(int(1 / Time::deltaTime));
			SetWindowText(m_Window->getHandle(), title.c_str());
			lastFrameChange = 0.0f;
		} // TODO scoatel

		for (const auto& Layer : m_Layers)
			if (Layer->m_Active)
			{
				Layer->onUpdate(Time::deltaTime);
				//Layer->UiManager->onRender();
			}

		Renderer::endScene();

		lastFrameChange += Time::deltaTime;

		m_Window->pollEvents();

		if (GetAsyncKeyState(VK_ESCAPE))
			m_Window->isRunning() = false; // TODO scoatel

		oldTime = timeNow;
	}

}