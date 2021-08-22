#pragma once

#include "Application.h"

class Layer
{
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void onAttach() { }
	virtual void onDetach() { }
	virtual void onUpdate(float dt) { }

	std::shared_ptr<ScreenBuffer>& getBuffer() { return Application::Get()->m_Buffer; }
	std::shared_ptr<Camera>& getCamera() { return Application::Get()->m_Camera; }
	std::shared_ptr<Window>& getWindow() { return Application::Get()->m_Window; }
};