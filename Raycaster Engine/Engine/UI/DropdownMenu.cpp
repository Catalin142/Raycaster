#include "Core/RaycastPCH.h"
#include "Renderer/Renderer.h"
#include "DropdownMenu.h"

DropdownMenu::DropdownMenu(const std::shared_ptr<Sprite>& spr, float width, float height) : InteractableUI(spr, width, height)
{ 
	m_Callback = [&]() { m_isOpened = !m_isOpened; };
}

DropdownMenu::DropdownMenu(const std::string& filepath, float width, float height) : InteractableUI(filepath, width, height)
{ 
	m_Callback = [&]() { m_isOpened = !m_isOpened; };
}

DropdownMenu::DropdownMenu(const vec3& color, float width, float height) : InteractableUI(color, width, height)
{ 
	m_Callback = [&]() { m_isOpened = !m_isOpened; };
}

void DropdownMenu::Render()
{
	if (m_Sprite != nullptr)
		Renderer::renderSprite(m_Sprite, m_Position, m_PixelDimensions, m_Color);
	else Renderer::drawQuad(m_Position, { (float)m_Width, (float)m_Height }, m_Color);

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

void DropdownMenu::addButton(const std::string& name, std::shared_ptr<Button>& button)
{
	if (m_Buttons.find(name) == m_Buttons.end())
	{
		button->setSize(m_Width, m_Height);

		m_Buttons[name] = button;
		button->setPosition({ m_Position.x, m_Position.y - (m_Buttons.size() * (m_Height + 1)) });
	}
}

std::shared_ptr<Button>& DropdownMenu::operator[](const char* name)
{
	return m_Buttons[name];
}
