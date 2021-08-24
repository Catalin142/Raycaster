#include "Core/RaycastPCH.h"
#include "Font.h"

std::unordered_map<std::string, std::shared_ptr<Font>> FontManager::m_Fonts;

Font::Font(const std::string& path, int glyphWidth, int glyphHeight) : m_GlyphWidth(glyphWidth), m_GlyphHeight(glyphHeight)
{
	m_FontSheet = std::make_shared<Sprite>(path);
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
