#include "Core/RaycastPCH.h"
#include "InputBox.h"
#include "Utils/Input.h"
#include "Renderer/Renderer.h"

InputBox::InputBox(const std::shared_ptr<Sprite>& spr, float width, float height) : InteractableUI(spr, width, height)
{
	m_Callback = [&]() { m_WaitForInput = true; };
}

InputBox::InputBox(const std::string& filepath, float width, float height) : InteractableUI(filepath, width, height)
{
	m_Callback = [&]() { m_WaitForInput = true; };
}

InputBox::InputBox(const vec3& color, float width, float height) : InteractableUI(color, width, height)
{
	m_Callback = [&]() { m_WaitForInput = true; };
}

bool InputBox::onMousePressed(int mousex, int mousey)
{
	bool pressed = (m_Position.x + m_Width > mousex && m_Position.x < mousex&&
		m_Position.y + m_Height > mousey && m_Position.y < mousey);

	if (pressed)
		m_Callback();
	else m_WaitForInput = false;

	return pressed;
}

void InputBox::onKeyDown(int code)
{
	Input::blockInput(m_WaitForInput);
	if (m_WaitForInput == true)
	{
		if (code == VK_BACK)
			m_Buffer.pop_back();

		else if (code == VK_RETURN)
			m_WaitForInput = false;

		else
		{
			m_Buffer += char(code);
		}

		setText(m_Buffer);
	}
}
