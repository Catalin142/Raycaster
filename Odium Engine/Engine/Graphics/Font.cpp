#include "Core/RaycastPCH.h"
#include "Font.h"

std::shared_ptr<Sprite> Font::m_FontSheet;
std::shared_ptr<Sprite> Font::m_NumbersSheet;
std::shared_ptr<Sprite> Font::m_SymbolsSheet;

uint Font::m_GlyphHeight;
uint Font::m_GlyphWidth;

std::unordered_map<char, int> Font::m_GlyphSize;

void Font::Init(const std::string& path, const std::string& numbers, const std::string& symbols, int glyphWidth, int glyphHeight)
{
	m_FontSheet = std::make_shared<Sprite>(path);
	m_NumbersSheet = std::make_shared<Sprite>(numbers);

	m_GlyphWidth = glyphWidth;
	m_GlyphHeight = glyphHeight;

	m_GlyphSize['a'] = glyphWidth - 2;
	m_GlyphSize['b'] = glyphWidth - 2;
	m_GlyphSize['c'] = glyphWidth - 2;
	m_GlyphSize['d'] = glyphWidth - 2;
	m_GlyphSize['e'] = glyphWidth - 2;
	m_GlyphSize['f'] = glyphWidth - 2;
	m_GlyphSize['g'] = glyphWidth - 2;
	m_GlyphSize['h'] = glyphWidth - 2;
	m_GlyphSize['i'] = glyphWidth - 5;
	m_GlyphSize['j'] = glyphWidth - 2;
	m_GlyphSize['k'] = glyphWidth - 2;
	m_GlyphSize['l'] = glyphWidth - 2;
	m_GlyphSize['m'] = glyphWidth - 1;
	m_GlyphSize['n'] = glyphWidth - 2;
	m_GlyphSize['o'] = glyphWidth - 2;
	m_GlyphSize['p'] = glyphWidth - 2;
	m_GlyphSize['q'] = glyphWidth - 2;
	m_GlyphSize['r'] = glyphWidth - 2;
	m_GlyphSize['s'] = glyphWidth - 2;
	m_GlyphSize['t'] = glyphWidth - 1;
	m_GlyphSize['u'] = glyphWidth - 2;
	m_GlyphSize['v'] = glyphWidth - 1;
	m_GlyphSize['w'] = glyphWidth - 1;
	m_GlyphSize['x'] = glyphWidth - 3;
	m_GlyphSize['y'] = glyphWidth - 2;
	m_GlyphSize['z'] = glyphWidth - 2;
	m_GlyphSize['0'] = glyphWidth - 2;
	m_GlyphSize['1'] = glyphWidth - 4;
	m_GlyphSize['2'] = glyphWidth - 2;
	m_GlyphSize['3'] = glyphWidth - 2;
	m_GlyphSize['4'] = glyphWidth - 2;
	m_GlyphSize['5'] = glyphWidth - 2;
	m_GlyphSize['6'] = glyphWidth - 2;
	m_GlyphSize['7'] = glyphWidth - 2;
	m_GlyphSize['8'] = glyphWidth - 2;
	m_GlyphSize['9'] = glyphWidth - 2;
}

uint Font::getGlyphWidth(char c)
{	 
	if (std::isupper(c))
		c = tolower(c);

	return m_GlyphSize[c];
}

uint Font::getTextWidth(const std::string& text)
{
	if (text.empty())
		return 0;

	uint size = 0;	
	
	for (int i = 0; i < text.size() - 1; i++)
	{
		if (text[i] != ' ')
			size += getGlyphWidth(text[i]) + 1;
		else size += 5;
	}
	size += getGlyphWidth(text[text.size() - 1]);

	return size;
}