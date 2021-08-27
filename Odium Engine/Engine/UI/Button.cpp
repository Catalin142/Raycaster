#include "Core/RaycastPCH.h"
#include "Button.h"
#include "Renderer/Renderer.h"
#include "Utils/Input.h"

#include "Events/MouseEvents.h"

Button::Button(const std::shared_ptr<Sprite>& spr, const std::shared_ptr<Font>& font, float width, float height) : InteractableUI(spr, font, width, height)
{ }

Button::Button(const std::string& filepath, const std::shared_ptr<Font>& font, float width, float height) : InteractableUI(filepath, font, width, height)
{ }

Button::Button(const vec3 & color, const std::shared_ptr<Font>& font, float width, float height) : InteractableUI(color, font, width, height)
{ }


bool Button::onMousePressed(int mousex, int mousey)
{
	bool pressed = (m_Position.x + m_Dimensions.x > mousex && m_Position.x < mousex &&
		m_Position.y + m_Dimensions.y >mousey && m_Position.y < mousey);

	if (pressed)
		m_Callback();
	return pressed;
}

bool Button::isHovered()
{
	vec2 mousePos = WindowToBufferCoordonates(getMousePosition());

	return (m_Position.x + m_Dimensions.x > mousePos.x && m_Position.x < mousePos.x&&
		m_Position.y + m_Dimensions.y > mousePos.y && m_Position.y < mousePos.y);
}
