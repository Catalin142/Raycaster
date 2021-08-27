#pragma once

#include "Graphics/Sprite.h"
#include "Utils/Maths.h"
#include "Graphics/Font.h"

class InteractableUI
{
public:
	InteractableUI(const std::shared_ptr<Sprite>& spr, const std::shared_ptr<Font>& font, float width, float height);
	InteractableUI(const std::string& filepath, const std::shared_ptr<Font>& font, float width, float height);
	InteractableUI(const vec3& color, const std::shared_ptr<Font>& font, float width, float height);

	virtual ~InteractableUI() = default;

	void setPosition(const vec2& pos) { m_Position = pos; }
	void setSize(float x, float y);
	void setColor(const vec3& color) { m_Color = color; }

	void setText(const std::string& text, int flags, const vec3& color);

	void setCallback(const std::function<void()>& func) { m_Callback = func; }

	virtual bool onMousePressed(int mousex, int mousey) = 0;
	virtual bool isHovered() = 0;

	void Render();

protected:
	std::shared_ptr<Sprite> m_Sprite = nullptr;
	std::shared_ptr<Font> m_Font;

	vec2 m_Position = { 0.0f, 0.0f };
	vec3 m_Color = { 1.0f, 1.0f, 1.0f };

	float m_Width;
	float m_Height;
	vec2 m_Dimensions;

	int m_Flags = 0;
	std::string m_Text;
	vec2 m_TextPosition = { 0.0f, 0.0f };
	vec3 m_TextColor = { 0.0f, 0.0f, 0.0f };

	std::function<void()> m_Callback = []() { std::cout << "a"; };
};