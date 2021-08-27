#pragma once
#include "Sprite.h"
#include "Utils/Types.h"

class Font
{
	friend class Renderer;
	friend class TextBox;
	friend class InteractableUI;

public:
	Font(const std::string& path, int glyphWidth, int glyphHeight);
	~Font() = default;

	uint getWidthGlyph(char c) { return m_CharacterSize[c - 'a']; }
	uint getTextWidth(const std::string& text);

private:
	std::shared_ptr<Sprite> m_FontSheet;

	uint m_GlyphHeight;
	uint m_GlyphWidth;

	uint m_CharacterSize[26];
};

class FontManager
{
public:
	static void addFont(const std::string& name, const std::shared_ptr<Font>& font);
	static std::shared_ptr<Font> getFont(const std::string& name);
	static void removeFont(const std::string& name);

private:
	static std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts;

private:
	FontManager() = default;
	~FontManager() = default;
};