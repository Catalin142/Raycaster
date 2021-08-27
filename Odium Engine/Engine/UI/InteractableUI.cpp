#include "Core/RaycastPCH.h"
#include "InteractableUI.h"

#include "Renderer/Renderer.h"
#include "Utils/Input.h"

InteractableUI::InteractableUI(const std::shared_ptr<Sprite>& spr, const std::shared_ptr<Font>& font, float width, float height) : m_Sprite(spr), m_Font(font),
m_Width(width / (float)spr->m_Width),
m_Height(height / (float)spr->m_Height),
m_Dimensions(width, height)
{ }

InteractableUI::InteractableUI(const std::string& filepath, const std::shared_ptr<Font>& font, float width, float height) : m_Sprite(std::make_shared<Sprite>(filepath)), m_Font(font),
m_Width(width / (float)m_Sprite->m_Width),
m_Height(height / (float)m_Sprite->m_Width),
m_Dimensions(width, height)
{ }

InteractableUI::InteractableUI(const vec3& color, const std::shared_ptr<Font>& font, float width, float height) : m_Color(color), m_Font(font), m_Width(width), m_Height(height),
m_Dimensions(width, height)
{ }

void InteractableUI::setSize(float x, float y)
{
	m_Width = x;
	m_Height = y;

	if (m_Sprite != nullptr)
		m_Dimensions = { m_Width / (float)m_Sprite->m_Width, m_Height / (float)m_Sprite->m_Height };
	else m_Dimensions = { m_Width, m_Height };
}

void InteractableUI::setText(const std::string& text, int flags, const vec3& color)
{
	m_Flags = flags;
	m_Text = text;
	m_TextColor = color;
	std::for_each(m_Text.begin(), m_Text.end(), [](char& c) { c = std::tolower(c); });

	uint currentTextSize = m_Font->getTextWidth(m_Text);

	m_TextPosition = m_Position;

	if (m_Flags & Center)
	{
		m_TextPosition.x = m_Position.x + m_Dimensions.x / 2.0f - currentTextSize / 2.0f;
		m_TextPosition.y = m_Position.y + m_Dimensions.y / 2.0f - m_Font->m_GlyphHeight / 2.0f;
	}

	if (m_Flags & Bottom)
		m_TextPosition.y = m_Position.y + m_Font->m_GlyphHeight;

	else if (m_Flags & Top)
		m_TextPosition.y = m_Position.y + m_Dimensions.y - m_Font->m_GlyphHeight;

	if (m_Flags & Left)
		m_TextPosition.x = m_Position.x;

	else if (m_Flags & Right)
		m_TextPosition.x = m_Position.x + m_Dimensions.x - currentTextSize;

}

void InteractableUI::Render()
{
	if (m_Sprite != nullptr)
		Renderer::renderSprite(m_Sprite, m_Position, { (float)m_Width, (float)m_Height }, m_Color);
	else Renderer::drawQuad(m_Position, { (float)m_Width, (float)m_Height }, m_Color);

	if (!m_Text.empty())
		Renderer::drawText(m_Text, m_Font, m_TextPosition, 1, m_TextColor);
}
