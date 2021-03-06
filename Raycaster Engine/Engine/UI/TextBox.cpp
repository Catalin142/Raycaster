#include "Core/RaycastPCH.h"
#include "TextBox.h"
#include "Tools/Benchmark.h"

#include "Renderer/Renderer.h"

TextBox::TextBox(const std::shared_ptr<Sprite>& fr, float width, float height) : m_Frame(fr), 
m_Width(width / (float)fr->m_Width), 
m_Height(height / (float)fr->m_Height)
{ }

TextBox::TextBox(const std::string & filepath, float width, float height) : m_Frame(std::make_shared<Sprite>(filepath)),
m_Width(width / (float)m_Frame->m_Width),
m_Height(height / (float)m_Frame->m_Height)
{ }

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
			Renderer::drawText(m_SubStrings[i].m_String, m_SubStrings[i].m_Position, 1, m_TextLayout.m_Color);
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

	m_Position = m_Position + m_Margin;
}

// ca sa fie putin mai rapid
// iau fiecare rand din text ii gasesc pozitia si tot ce trebe si dupa il adaug in vector si dupa randez in functia de mai sus  :)
void TextBox::setText(const std::string& text, int flags, const vec3& color)
{
	START_SCOPE_PROFILE("Set text");
	vec2 dim = { m_Width * m_Frame->m_Width, m_Height * m_Frame->m_Height };

	m_Text = text;

	m_TextLayout.m_TextWidth = Font::getTextWidth(m_Text, m_TextLayout.m_TextSize);
	m_TextLayout.m_Rows = std::ceil((float)m_TextLayout.m_TextWidth / (float)(dim.x - m_xOffset * 2));
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
			startintYposition = m_Position.y + ((float)dim.y / 2.0f) + (((float)Font::getGlyphHeight() * m_TextLayout.m_TextSize / 2.0f) * n);
		}

		else
			startintYposition = m_Position.y + ((float)dim.y / 2.0f) - ((float)Font::getGlyphHeight() * m_TextLayout.m_TextSize / 2.0f) +
			(Font::getGlyphHeight() * m_TextLayout.m_TextSize * ((m_TextLayout.m_Rows - 1.0f) / 2.0f));
	}

	if (m_TextLayout.m_Flags & Bottom)
		startintYposition = m_Position.y + (m_TextLayout.m_Rows - 1) * Font::getGlyphHeight();

	if (m_TextLayout.m_Flags & Top)
		startintYposition = m_Position.y + dim.y - Font::getGlyphHeight() * m_TextLayout.m_TextSize;

	int nTotalInsertedCharacters = 0;
	for (int i = 0; i < m_TextLayout.m_Rows; i++)
	{
		std::string currentString;

		int nCharacters = 0;
		int nTextWidth = 0;

		bool full = false;
		while (nTextWidth < dim.x - (m_xOffset * 2))
		{
			if (nCharacters >= totalCharacters)
				break;

			auto c = *(m_Text.begin() + nTotalInsertedCharacters + nCharacters);

			if (c == '\n')
			{
				m_TextLayout.m_Rows++;
				nCharacters++;

				break;
			}

			currentString += c;
			if (c == ' ')
				nTextWidth += 5;
			else nTextWidth += Font::getGlyphWidth(c) * m_TextLayout.m_TextSize + 1;

			nCharacters++;

			if (nTextWidth >= dim.x - (m_xOffset * 2) - 1)
				full = true;
		}

		if (!currentString.empty() && full)
		{
			int index = currentString.find_last_of(' ');
			if (index != -1)
			{
				nCharacters = nCharacters - (currentString.size() - (index + 1));
				currentString.erase(currentString.begin() + index, currentString.end());
			}
		}


		vec2 Pos = m_Position;

		if (m_TextLayout.m_Flags & Center)
		{
			Pos.x = m_Position.x + dim.x / 2.0f - nTextWidth / 2.0f;
			Pos.y = startintYposition;
		}

		if (m_TextLayout.m_Flags & Left)
			Pos.x = m_Position.x + m_xOffset;

		else if (m_TextLayout.m_Flags & Right)
			Pos.x = m_Position.x + dim.x - nTextWidth - m_xOffset;

		if (m_TextLayout.m_Flags & Bottom)
			Pos.y = startintYposition + m_yOffset;

		else if (m_TextLayout.m_Flags & Top)
			Pos.y = startintYposition - m_yOffset;

		nTotalInsertedCharacters += nCharacters;
		totalCharacters -= nCharacters;
		startintYposition -= Font::getGlyphHeight() * m_TextLayout.m_TextSize;

		m_SubStrings.push_back({ currentString, Pos });
	}
}