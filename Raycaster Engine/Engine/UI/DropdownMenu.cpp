#include "Core/RaycastPCH.h"
#include "Renderer/Renderer.h"
#include "DropdownMenu.h"
#include "Events/MouseEvents.h"

DropdownMenu::DropdownMenu(const std::shared_ptr<Sprite>& spr, float width, float height) : InteractableUI(spr, width, height)
{ 
	m_Callback = [&]() { m_isOpened = !m_isOpened; };
	m_Type = UIType::Dropdown;
}

DropdownMenu::DropdownMenu(const std::string& filepath, float width, float height) : InteractableUI(filepath, width, height)
{ 
	m_Callback = [&]() { m_isOpened = !m_isOpened; };
	m_Type = UIType::Dropdown;
}

DropdownMenu::DropdownMenu(const vec3& color, float width, float height) : InteractableUI(color, width, height)
{ 
	m_Callback = [&]() { m_isOpened = !m_isOpened; };
	m_Type = UIType::Dropdown;
}

void DropdownMenu::Render()
{
	if (m_Sprite != nullptr)
		Renderer::renderSprite(m_Sprite, m_Position, m_PixelDimensions, m_Color);
	else
	{
		Renderer::drawQuad(m_Position, { (float)m_Width, (float)m_Height }, m_Color);
		Renderer::plotQuad(m_Position, { (float)m_Width, (float)m_Height }, m_FrameColor);
	}

	if (!m_Text.empty())
		Renderer::drawText(m_Text, m_TextPosition, 1, m_TextColor);

	if (m_isOpened && !m_Buttons.empty())
	{
		for (const auto& Button : m_Buttons)
		{
			Button.second->Render();
			if (m_useFrame)
				Renderer::plotQuad(Button.second->m_Position, { Button.second->m_Width, Button.second->m_Height }, m_FrameColor);
		}
	}
}

bool DropdownMenu::onEvent(Event& event)
{
	if (m_isOpened)
		for (const auto& Button : m_Buttons)
		{
			if (event.getType() == EventType::MousePressed)
			{
				auto ev = static_cast<MousePressedEvent&>(event);
				if (ev.getMouseCode() == VK_MOUSE_LEFT)
				{
					vec2 mousePos = Input::WindowToBufferCoordonates({ (float)ev.getX(), (float)ev.getY() });
					if (Button.second->onMousePressed(mousePos.x, mousePos.y))
					{
						m_isOpened = false;
						return true;
					}
				}
			}
		}
	return false;
}

void DropdownMenu::addButton(const std::string& name, std::shared_ptr<Button>& button)
{
	if (m_Buttons.find(name) == m_Buttons.end())
	{
		button->setSize(m_Width, m_Height);
		m_Buttons[name] = button;
		button->setPosition({ m_Position.x, m_Position.y - (m_Buttons.size() * (m_Height + 1)) });
		button->setText(name, Center, m_TextColor);
	}
}

std::shared_ptr<Button>& DropdownMenu::operator[](const char* name)
{
	return m_Buttons[name];
}