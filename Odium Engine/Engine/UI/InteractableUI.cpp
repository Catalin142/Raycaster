#include "Core/RaycastPCH.h"
#include "InteractableUI.h"

#include "Renderer/Renderer.h"
#include "Utils/Input.h"

InteractableUI::InteractableUI(const std::shared_ptr<Sprite>& spr, float width, float height) : m_Sprite(spr),
m_Width(width),
m_Height(height),
m_PixelDimensions(width / spr->m_Width, height / spr->m_Height)
{ }

InteractableUI::InteractableUI(const std::string& filepath, float width, float height) : m_Sprite(std::make_shared<Sprite>(filepath)),
m_Width(width),
m_Height(height),
m_PixelDimensions(width / m_Sprite->m_Width, height / m_Sprite->m_Height)
{ }

InteractableUI::InteractableUI(const vec3& color, float width, float height) : m_Color(color), m_Width(width), m_Height(height),
m_PixelDimensions(width, height)
{ }

void InteractableUI::setPosition(const vec2& pos)
{
	m_Position = pos;
}

void InteractableUI::setPosition(int flags)
{
	vec2 bufferDim = { (float)Application::Get()->getBuffer()->getWidth(), (float)Application::Get()->getBuffer()->getHeight() };

	if (flags & Center)
	{
		m_Position.x = bufferDim.x / 2.0f - m_Width / 2.0f;
		m_Position.y = bufferDim.y / 2.0f - m_Height / 2.0f;
	}

	if (flags & Left)
		m_Position.x = 0;

	else if (flags & Right)
		m_Position.x = bufferDim.x - m_Width;

	if (flags & Bottom)
		m_Position.y = 0;

	else if (flags & Top)
		m_Position.y = bufferDim.y - m_Height;
}

void InteractableUI::setSize(float x, float y)
{
	m_Width = x;
	m_Height = y;

	if (m_Sprite)
		m_PixelDimensions = { m_Width / m_Sprite->m_Width, m_Height / m_Sprite->m_Height };

}

void InteractableUI::Refresh()
{
	if (!m_Text.empty())
		setText(m_Text);
}

void InteractableUI::setText(const std::string& text)
{
	m_Text = text;

	uint currentTextSize = Font::getTextWidth(m_Text);

	m_TextPosition = m_Position;

	if (m_Flags & Center)
	{
		m_TextPosition.x = m_Position.x + m_Width / 2.0f - currentTextSize / 2.0f;
		m_TextPosition.y = m_Position.y + m_Height / 2.0f - Font::m_GlyphHeight / 2.0f;
	}

	if (m_Flags & Bottom)
		m_TextPosition.y = m_Position.y + Font::m_GlyphHeight;

	else if (m_Flags & Top)
		m_TextPosition.y = m_Position.y + m_Height - Font::m_GlyphHeight;

	if (m_Flags & Left)
		m_TextPosition.x = m_Position.x;

	else if (m_Flags & Right)
		m_TextPosition.x = m_Position.x + m_Width - currentTextSize;

}

void InteractableUI::Render()
{
	if (m_Sprite != nullptr)
		Renderer::renderSprite(m_Sprite, m_Position, m_PixelDimensions, m_Color);
	else Renderer::drawQuad(m_Position, { (float)m_Width, (float)m_Height }, m_Color);

	if (!m_Text.empty())
		Renderer::drawText(m_Text, m_TextPosition, 1, m_TextColor);
}

bool InteractableUI::onMousePressed(int mousex, int mousey)
{
	bool pressed = (m_Position.x + m_Width > mousex && m_Position.x < mousex&&
		m_Position.y + m_Height > mousey && m_Position.y < mousey);

	if (pressed)
		m_Callback();
	return pressed;
}

bool InteractableUI::isHovered()
{
	vec2 mousePos = Input::WindowToBufferCoordonates(Input::getMousePosition());

	return (m_Position.x + m_Width > mousePos.x && m_Position.x < mousePos.x&&
		m_Position.y + m_Height > mousePos.y && m_Position.y < mousePos.y);
}
