#include "Core/RaycastPCH.h"
#include "UIManager.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Utils/Input.h"
#include "DropdownMenu.h"

void UIManager::addButton(const char* name, const std::shared_ptr<Button>& button)
{
	auto it = std::find_if(m_UIElements.begin(), m_UIElements.end(), [&](const UIElement& elem) -> bool {
		return elem.Name == name;
		});

	if (it == m_UIElements.end())
	{
		UIElement elem;
		elem.Name = name;
		elem.UI = button;
		m_UIElements.push_back(elem);
	}
}

void UIManager::addDropdownMenu(const char* name, const std::shared_ptr<DropdownMenu>& menu)
{
	auto it = std::find_if(m_UIElements.begin(), m_UIElements.end(), [&](const UIElement& elem) -> bool {
		return elem.Name == name;
		});

	if (it == m_UIElements.end())
	{
		UIElement elem;
		elem.Name = name;
		elem.UI = menu;
		m_UIElements.push_back(elem);
	}
}

std::shared_ptr<InteractableUI>& UIManager::operator[](const char* name)
{
	auto it = std::find_if(m_UIElements.begin(), m_UIElements.end(), [&](const UIElement& elem) -> bool {
		return elem.Name == name;
		});

	if (it != m_UIElements.end())
		return it->UI;
}

bool UIManager::onEvent(Event& event)
{
	for (auto& it = m_UIElements.rbegin(); it != m_UIElements.rend(); it++)
	{
		if (it->UI->getInteractionType() & Mouse && event.getType() == EventType::MousePressed)
		{
			auto ev = static_cast<MousePressedEvent&>(event);
			if (ev.getMouseCode() == VK_MOUSE_LEFT)
			{
				vec2 mousePos = Input::WindowToBufferCoordonates({ (float)ev.getX(), (float)ev.getY() });
				if (it->UI->onMousePressed(mousePos.x, mousePos.y))
					return true;
			}
		}

		if (it->UI->getType() == UIType::Dropdown)
			std::static_pointer_cast<DropdownMenu>(it->UI)->onEvent(event);
	}
}

void UIManager::onRender()
{
	for (auto& it = m_UIElements.cbegin(); it != m_UIElements.cend(); it++)
		it->UI->Render();
}
