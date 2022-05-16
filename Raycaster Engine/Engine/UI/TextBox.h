#pragma once

#include "Graphics/Sprite.h"
#include "Graphics/Font.h"

class TextBox
{
public:
	TextBox(const std::shared_ptr<Sprite>& fr, float width, float height);
	TextBox(const std::string& filepath, float width, float height);
	~TextBox() = default;

	void Render();
	
	void setPosition(const vec2& pos) { m_Position = pos; }
	void setPosition(int flags);
	void setMargin(const vec2& margin) { m_Margin = margin; }

	void setText(const std::string& text, int flags, const vec3& color);

	void setOffset(int x, int y) { m_xOffset = x; m_yOffset = y; }

private:
	std::shared_ptr<Sprite> m_Frame;

	float m_Width;
	float m_Height;
	vec2 m_Margin = { 0.0f, 0.0f };

	vec2 m_Position = { 0.0f, 0.0f };

	std::string m_Text;

	struct TextLayout
	{
		int m_Rows;
		int m_TextWidth;
		int m_Flags;
		vec3 m_Color;
		int m_TextSize = 1;

	} m_TextLayout;

	struct SubString
	{
		std::string m_String;
		vec2 m_Position;
	};

	std::vector<SubString> m_SubStrings; // daca am mai mult de 1 rand

	int m_xOffset = 0;
	int m_yOffset = 0;
};