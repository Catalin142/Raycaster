#include "Core/RaycastPCH.h"
#include "Font.h"

std::unordered_map<std::string, std::shared_ptr<Font>> FontManager::m_Fonts;

Font::Font(const std::string& path, int glyphWidth, int glyphHeight) : m_GlyphWidth(glyphWidth), m_GlyphHeight(glyphHeight)
{
	m_FontSheet = std::make_shared<Sprite>(path);
	m_CharacterSize['a' - 'a'] = glyphWidth - 2;
	m_CharacterSize['b' - 'a'] = glyphWidth - 2;
	m_CharacterSize['c' - 'a'] = glyphWidth - 2;
	m_CharacterSize['d' - 'a'] = glyphWidth - 2;
	m_CharacterSize['e' - 'a'] = glyphWidth - 2;
	m_CharacterSize['f' - 'a'] = glyphWidth - 2;
	m_CharacterSize['g' - 'a'] = glyphWidth - 2;
	m_CharacterSize['h' - 'a'] = glyphWidth - 2;
	m_CharacterSize['i' - 'a'] = glyphWidth - 5;
	m_CharacterSize['j' - 'a'] = glyphWidth - 2;
	m_CharacterSize['k' - 'a'] = glyphWidth - 2;
	m_CharacterSize['l' - 'a'] = glyphWidth - 2;
	m_CharacterSize['m' - 'a'] = glyphWidth - 1;
	m_CharacterSize['n' - 'a'] = glyphWidth - 2;
	m_CharacterSize['o' - 'a'] = glyphWidth - 2;
	m_CharacterSize['p' - 'a'] = glyphWidth - 2;
	m_CharacterSize['q' - 'a'] = glyphWidth - 2;
	m_CharacterSize['r' - 'a'] = glyphWidth - 2;
	m_CharacterSize['s' - 'a'] = glyphWidth - 2;
	m_CharacterSize['t' - 'a'] = glyphWidth - 1;
	m_CharacterSize['u' - 'a'] = glyphWidth - 2;
	m_CharacterSize['v' - 'a'] = glyphWidth - 1;
	m_CharacterSize['w' - 'a'] = glyphWidth - 1;
	m_CharacterSize['x' - 'a'] = glyphWidth - 3;
	m_CharacterSize['y' - 'a'] = glyphWidth - 2;
	m_CharacterSize['z' - 'a'] = glyphWidth - 2;
}

uint Font::getTextWidth(const std::string& text)
{
	uint size = 0;

	for (int i = 0; i < text.size() - 1; i++)
	{
		if (text[i] != ' ')
			size += getWidthGlyph(text[i]) + 1;
		else size += 5;
	}
	size += getWidthGlyph(text[text.size() - 1]);

	return size;
}

void FontManager::addFont(const std::string& name, const std::shared_ptr<Font>& font)
{
	if (m_Fonts.find(name) == m_Fonts.end())
		m_Fonts[name] = font;
}

std::shared_ptr<Font> FontManager::getFont(const std::string& name)
{
	if (m_Fonts.find(name) != m_Fonts.end())
		return m_Fonts[name];
}

void FontManager::removeFont(const std::string& name)
{
	if (m_Fonts.find(name) != m_Fonts.end())
		m_Fonts.erase(name);
}
