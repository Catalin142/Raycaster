#pragma once

#include "Graphics/Sprite.h"
#include "Utils/Maths.h"
#include "Graphics/Font.h"
#include "Renderer/Renderer.h"

class InteractableUI
{
public:
	InteractableUI(const std::shared_ptr<Sprite>& spr, float width, float height);
	InteractableUI(const std::string& filepath, float width, float height);
	InteractableUI(const vec3& color, float width, float height);

	virtual ~InteractableUI() = default;

	void setPosition(const vec2& pos);
	void setPosition(int flags);

	void setSize(float x, float y);

	void setColor(const vec3& color) { m_Color = color; }
	void Refresh();

	void setText(const std::string& text, int flags, const vec3& color) { setTextAlignment(flags), setTextColor(color), setText(text); }
	void setText(const std::string& text);
	void setTextAlignment(int flags) { m_Flags = flags; }
	void setTextColor(const vec3& color) { m_TextColor = color; }

	void setCallback(const std::function<void()>& func) { m_Callback = func; }

	virtual bool onMousePressed(int mousex, int mousey);
	virtual bool isHovered();

	virtual void Render();

protected:
	std::shared_ptr<Sprite> m_Sprite = nullptr;

	vec2 m_Position = { 0.0f, 0.0f };
	vec3 m_Color = { 1.0f, 1.0f, 1.0f };

	float m_Width;
	float m_Height;
	vec2 m_PixelDimensions;

	int m_Flags = Center;
	std::string m_Text;
	vec2 m_TextPosition = { 0.0f, 0.0f };
	vec3 m_TextColor = { 0.0f, 0.0f, 0.0f };

	std::function<void()> m_Callback = []() { std::cout << "a"; };
};