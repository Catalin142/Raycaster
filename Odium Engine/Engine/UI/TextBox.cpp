#include "Core/RaycastPCH.h"
#include "TextBox.h"

#include "Renderer/Renderer.h"

TextBox::TextBox(const std::shared_ptr<Sprite>& fr, const std::shared_ptr<Font>& font, float width, float height) : m_Frame(fr), m_Font(font), 
m_Width(width / (float)fr->m_Width), 
m_Height(height / (float)fr->m_Height)
{  }

TextBox::TextBox(const std::string & filepath, const std::shared_ptr<Font>&font, float width, float height) : m_Frame(std::make_shared<Sprite>(filepath)),
m_Font(font), 
m_Width(width / (float)m_Frame->m_Width),
m_Height(height / (float)m_Frame->m_Height)
{
}

int row = 0;
void TextBox::Render()
{
	Renderer::renderSprite(m_Frame, m_Position, { (float)m_Width, (float)m_Height });

	if (m_Text.empty())
	{
		assert(0);
		return;
	}

	else
	{
		for (int i = row; i < m_SubStrings.size(); i++)
			Renderer::drawText(m_SubStrings[i].m_String, m_Font, m_SubStrings[i].m_Position, 1, m_TextLayout.m_Color);
	}

}

void TextBox::setPosition(int flags)
{
	vec2 dim = { m_Frame->m_Width * m_Width, m_Frame->m_Height * m_Height };
	vec2 bufferDim = { (float)Application::Get()->getBuffer()->getWidth(), (float)Application::Get()->getBuffer()->getHeight() };

	if (flags & Center)
	{
		m_Position.x = bufferDim.x / 2.0f - dim.x / 2.0f;
		m_Position.y = bufferDim.y / 2.0f - dim.y / 2.0f;
	}

	if (flags & Left)
		m_Position.x = 0;

	else if (flags & Right)
		m_Position.x = bufferDim.x - dim.x;

	if (flags & Bottom)
		m_Position.y = 0;

	else if (flags & Top)
		m_Position.y = bufferDim.y - dim.y;
}

// ca sa fie putin mai rapid
// iau fiecare rand din text ii gasesc pozitia si tot ce trebe si dupa il adaug in vector si dupa randez in functia de mai sus  :)
void TextBox::setText(const std::string& text, int flags, const vec3& color)
{
	vec2 dim = { m_Frame->m_Width * m_Width, m_Frame->m_Height * m_Height };

	m_SubStrings.clear();

	m_Text = text;
	std::for_each(m_Text.begin(), m_Text.end(), [](char& c) { c = std::tolower(c); });

	m_TextLayout.m_TextSize = m_Font->getTextWidth(m_Text);
	m_TextLayout.m_CharactersOnRow = dim.x / m_Font->m_GlyphWidth - 2;
	m_TextLayout.m_Rows = std::ceil((float)m_TextLayout.m_TextSize / (float)dim.x);
	m_TextLayout.m_Flags = flags;
	m_TextLayout.m_Color = color;

	int totalCharacters = text.size();

	float startintYposition = 0;

	if (m_TextLayout.m_Flags & Center)
	{
		if (m_TextLayout.m_Rows % 2 == 0)
		{
			float n;
			if (m_TextLayout.m_Rows == 2)
				n = 0;
			else n = (float)m_TextLayout.m_Rows / 2.0f;
			startintYposition = m_Position.y + ((float)dim.y / 2.0f) + (((float)m_Font->m_GlyphHeight / 2.0f) * n);
		}

		else
			startintYposition = m_Position.y + ((float)dim.y / 2.0f) - ((float)m_Font->m_GlyphHeight / 2.0f) + (m_Font->m_GlyphHeight *
				((m_TextLayout.m_Rows - 1.0f) / 2.0f));
	}

	if (m_TextLayout.m_Flags & Bottom)
		startintYposition = m_Position.y + (m_TextLayout.m_Rows - 1) * m_Font->m_GlyphHeight + m_yOffset;

	if (m_TextLayout.m_Flags & Top)
		startintYposition = m_Position.y + dim.y - m_Font->m_GlyphHeight - m_yOffset;

	for (int i = 0; i < m_TextLayout.m_Rows; i++)
	{
		std::string currentString(m_Text.begin() + i * m_TextLayout.m_CharactersOnRow,
			m_Text.begin() + i * m_TextLayout.m_CharactersOnRow + std::min(totalCharacters, m_TextLayout.m_CharactersOnRow));

		vec2 Pos = m_Position;

		float currentTextSize = m_Font->getTextWidth(currentString);

		if (m_TextLayout.m_Flags & Center)
		{
			Pos.x = m_Position.x + dim.x / 2.0f - currentTextSize / 2.0f;
			Pos.y = startintYposition;
		}

		if (m_TextLayout.m_Flags & Left)
			Pos.x = m_Position.x + m_xOffset;

		else if (m_TextLayout.m_Flags & Right)
			Pos.x = m_Position.x + dim.x - currentTextSize - m_xOffset;

		if (m_TextLayout.m_Flags & Bottom)
			Pos.y = startintYposition;

		else if (m_TextLayout.m_Flags & Top)
			Pos.y = startintYposition;

		totalCharacters -= m_TextLayout.m_CharactersOnRow;
		startintYposition -= m_Font->m_GlyphHeight;

		m_SubStrings.push_back({ currentString, Pos });
	}
}
