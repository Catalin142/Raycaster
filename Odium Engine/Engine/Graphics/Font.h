#pragma once
#include "Sprite.h"
#include "Utils/Types.h"

class Font
{
	friend class Renderer;
	friend class TextBox;

public:
	Font(const std::string& path, int glyphWidth, int glyphHeight);
	~Font() = default;

private:
	std::shared_ptr<Sprite> m_FontSheet;

	uint m_GlyphHeight;
	uint m_GlyphWidth;
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