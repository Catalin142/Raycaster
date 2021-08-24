#pragma once

#include "Graphics/Sprite.h"
#include "Graphics/Font.h"

class TextBox
{
public:
	TextBox(const std::shared_ptr<Sprite>& fr, const std::shared_ptr<Font>& font, int width, int height);
	~TextBox() = default;

	void Render();
	
	void setPosition(const vec2& pos) { m_Position = pos; }
	void setText(const std::string& text, int flags, const vec3& color);

private:
	std::shared_ptr<Sprite> m_Frame;
	std::shared_ptr<Font> m_Font;

	int m_Width;
	int m_Height;

	vec2 m_Position = { 0.0f, 0.0f };

	std::string m_Text;

	struct TextLayout
	{
		int m_Rows;
		int m_CharactersOnRow;
		int m_TextSize;
		int m_Flags;
		vec3 m_Color;

	} m_TextLayout;

	struct SubString
	{
		std::string m_String;
		vec2 m_Position;
	};

	std::vector<SubString> m_SubStrings; // daca am mai mult de 1 rand
};