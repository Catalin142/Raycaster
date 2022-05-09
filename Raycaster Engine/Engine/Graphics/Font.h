#pragma once
#include "Sprite.h"
#include "Utils/Types.h"

class Font
{
	friend class Renderer;
	friend class TextBox;
	friend class InteractableUI;

public:
	static void Init(const std::string& path, const std::string& numbers, const std::string& symbols, int glyphWidth, int glyphHeight);

	static uint getGlyphWidth(char c);

	static uint getSymbolWidth(char s);
	static uint getSymbolOffset(char s);

	static uint getTextWidth(const std::string& text);

	static bool Exists(char c);

private:
	static std::shared_ptr<Sprite> m_FontSheet;
	static std::shared_ptr<Sprite> m_NumbersSheet;
	static std::shared_ptr<Sprite> m_SymbolsSheet;

	static uint m_GlyphHeight;
	static uint m_GlyphWidth;

	static std::unordered_map<char, int> m_GlyphSize;

private:
	Font() = default;
	~Font() = default;
};