#pragma once

#include "Application.h"
#include "Events/EventListener.h"
#include "UI/UIManager.h"

class Layer : public EventListener
{
	friend class Application;
	friend class EventDispatcher;

public:
	Layer();
	virtual ~Layer() = default;

	virtual void onAttach() { }
	virtual void onDetach() { }
	virtual void onUpdate(float dt) { }
	virtual bool onEvent(Event& event) override { return UiManager->onEvent(event); }

	std::shared_ptr<ScreenBuffer>& getBuffer() { return Application::Get()->m_Buffer; }
	std::shared_ptr<Window>& getWindow() { return Application::Get()->m_Window; }

protected:
	std::shared_ptr<UIManager> UiManager;

private:
	bool m_Active = true;
};