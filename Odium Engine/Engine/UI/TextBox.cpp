#include "Core/RaycastPCH.h"
#include "TextBox.h"

#include "Renderer/Renderer.h"

TextBox::TextBox(const std::shared_ptr<Sprite>& fr, const std::shared_ptr<Font>& font, int width, int height) : m_Frame(fr), m_Font(font), m_Width(width), m_Height(height) 
{  }

void TextBox::Render()
{
	Renderer::renderSprite(m_Frame, m_Position, { float(m_Width / m_Frame->m_Width), float(m_Height / m_Frame->m_Height) });

	if (m_Text.empty())
	{
		assert(0);
		return;
	}

	else
	{
		for(const auto& subsr : m_SubStrings)
			Renderer::drawText(subsr.m_String, m_Font, subsr.m_Position, 1, m_TextLayout.m_Color);
	}

}

// ca sa fie putin mai rapid
// iau fiecare rand din text ii gasesc pozitia si tot ce trebe si dupa il adaug in vector si dupa randez in functia de mai sus  :)
void TextBox::setText(const std::string& text, int flags, const vec3& color)
{
	m_Text = text;

	m_TextLayout.m_TextSize = m_Text.length() * m_Font->m_GlyphWidth;
	m_TextLayout.m_CharactersOnRow = m_Width / m_Font->m_GlyphWidth - 2;
	m_TextLayout.m_Rows = std::ceil((float)m_TextLayout.m_TextSize / (float)m_Width);
	m_TextLayout.m_Flags = flags;
	m_TextLayout.m_Color = color;

	int totalCharacters = text.size();

	float startintYposition = 0;

	if (m_TextLayout.m_Flags & TextCenter)
	{
		if (m_TextLayout.m_Rows % 2 == 0)
		{
			float n;
			if (m_TextLayout.m_Rows == 2)
				n = 0;
			else n = (float)m_TextLayout.m_Rows / 2.0f;
			startintYposition = m_Position.y + ((float)m_Height / 2.0f) + (((float)m_Font->m_GlyphHeight / 2.0f) * n);
		}

		else
			startintYposition = m_Position.y + ((float)m_Height / 2.0f) - ((float)m_Font->m_GlyphHeight / 2.0f) + (m_Font->m_GlyphHeight * 
				((m_TextLayout.m_Rows - 1.0f) / 2.0f));
	}

	else if (m_TextLayout.m_Flags & TextBottom)
		startintYposition = m_Position.y + (m_TextLayout.m_Rows - 1) * m_Font->m_GlyphHeight + 5.0f;

	else if (m_TextLayout.m_Flags & TextTop)
		startintYposition = m_Position.y + m_Height - m_Font->m_GlyphHeight - 5.0f;

	for (int i = 0; i < m_TextLayout.m_Rows; i++)
	{
		std::string currentString(m_Text.begin() + i * m_TextLayout.m_CharactersOnRow,
			m_Text.begin() + i * m_TextLayout.m_CharactersOnRow + std::min(totalCharacters, m_TextLayout.m_CharactersOnRow));

		vec2 Pos = { 0.0f, 0.0f };

		float currentTextSize = currentString.length() * m_Font->m_GlyphWidth;

		if (m_TextLayout.m_Flags & TextCenter)
		{
			Pos.x = m_Position.x + m_Width / 2.0f - currentTextSize / 2.0f;
			Pos.y = startintYposition;
		}

		if (m_TextLayout.m_Flags & TextLeft)
			Pos.x = 0;

		else if (m_TextLayout.m_Flags & TextRight)
			Pos.x = m_Position.x + m_Width - currentTextSize;

		if (m_TextLayout.m_Flags & TextBottom)
			Pos.y = startintYposition;

		else if (m_TextLayout.m_Flags & TextTop)
			Pos.y = startintYposition;

		totalCharacters -= m_TextLayout.m_CharactersOnRow;
		startintYposition -= m_Font->m_GlyphHeight;
		m_SubStrings.push_back({ currentString, Pos });
	}
}
