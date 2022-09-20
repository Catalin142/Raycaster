#include "Core/RaycastPCH.h"
#include "Renderer.h"
#include "Utils/Color.h"

#include "Tools/Benchmark.h"

std::shared_ptr<ScreenBuffer> Renderer::m_Buffer;
std::shared_ptr<Camera> Renderer::m_Camera;

uint32* Renderer::m_BuffersBuffer;
float* Renderer::m_DepthBuffer;

 vec3 Renderer::m_ClearColor;

void Renderer::endScene()
{
	START_SCOPE_PROFILE("Draw");
	m_Buffer->Render();
}

void Renderer::Init(std::shared_ptr<ScreenBuffer>& buffer)
{
	m_Buffer = buffer;
	(uint32*)m_BuffersBuffer = (uint32*)m_Buffer->m_MemoryBuffer;
	m_DepthBuffer = m_Buffer->m_DepthBuffer;
}

void Renderer::Clear(float r, float g, float b)
{
	m_Buffer->Clear(r, g, b);
}

void Renderer::Clear()
{
	m_Buffer->Clear(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b);
}

void Renderer::setClearColor(float r, float g, float b)
{
	m_ClearColor = { r, g, b };
}

void Renderer::drawQuad(const vec2& pos, const vec2& size, unsigned long color)
{
	int startY = Clamp(pos.y, 0, m_Buffer->m_Height - 1.0f);
	int endY = Clamp(pos.y + size.y, 0, m_Buffer->m_Height - 1.0f);
	
	int startX = Clamp(pos.x, 0, m_Buffer->m_Width - 1.0f);
	int endX = Clamp(pos.x + size.x, 0, m_Buffer->m_Width - 1.0f);

	uint32* pixel;
	for (int y = startY; y < endY; y++)
	{
		pixel = (uint32*)m_BuffersBuffer + (int)startX + y * m_Buffer->m_Width;
		for (int x = startX; x < endX; x++)
		{
			*(pixel++) = color;
		}
	}
}

void Renderer::drawQuad(const vec2& pos, const vec2& size, const vec3& color)
{
	auto hexColor = createHex(color.r * 255, color.g * 255, color.b * 255);

	drawQuad(pos, size, hexColor);
}

void Renderer::plotQuad(const vec2& pos, const vec2& size, unsigned long color)
{
	drawLine(pos, pos + vec2(size.x, 0), color);
	drawLine(pos, pos + vec2(0, size.y), color);

	drawLine(pos + vec2(0, size.y - 1), pos + vec2(size.x, size.y), color);
	drawLine(pos + vec2(size.x - 1, 0), pos + vec2(size.x, size.y), color);
}

void Renderer::plotQuad(const vec2& pos, const vec2& size, const vec3& color)
{
	auto hexColor = createHex(color.r * 255, color.g * 255, color.b * 255);

	plotQuad(pos, size, hexColor);
}

void Renderer::setPixel(const vec2& pos, vec3 color)
{
	color.x = Clamp(color.x, 0.0f, 1.0f);
	color.y = Clamp(color.y, 0.0f, 1.0f);
	color.z = Clamp(color.z, 0.0f, 1.0f);
	int pixel = (int)pos.y * m_Buffer->m_Width + (int)pos.x;
	*(m_BuffersBuffer + pixel) = createHex(color.r * 255, color.g * 255, color.b * 255);
}

void Renderer::setPixel_s(const vec2& pos, const vec3& color)
{
	if (checkPixel(pos))
		return;
	setPixel(pos, color);
}

void Renderer::setPixel_n(const vec2& pos, const vec3& color)
{
	int pixel = (int)pos.y * m_Buffer->m_Width + (int)pos.x;
	*(m_BuffersBuffer + pixel) = createHex(color.r * 255, color.g * 255, color.b * 255);
}

void Renderer::setPixel(const vec2& pos, unsigned long hexColor)
{
	int pixel = (int)pos.y * m_Buffer->m_Width + (int)pos.x;
	*(m_BuffersBuffer + pixel) = hexColor;
}

void Renderer::setPixel_s(const vec2& pos, unsigned long hexColor)
{
	if (checkPixel(pos))
		return;
	setPixel(pos, hexColor);
}

void Renderer::renderScene(const std::shared_ptr<Scene>& scene)
{
	for (const auto& ent : scene->m_Entities)
	{
		if (ent->m_Visible)
			ent->onDraw(scene);
	}
}

void Renderer::setDepthPixel(int column, float depth)
{
	*(m_DepthBuffer + column) = depth;
}

float Renderer::getPixelDepth(int column)
{
	if (column >= 0 && column < m_Buffer->getWidth())
		return *(m_DepthBuffer + column);
}

bool Renderer::checkPixel(const vec2& pos)
{
	return (pos.x > m_Buffer->m_Width - 1.0f || pos.y > m_Buffer->m_Height - 1.0f || pos.x < 0 || pos.y < 0);
}

// Bresenham alg http://members.chello.at/~easyfilter/bresenham.html
void Renderer::drawLine(const vec2& begin, const vec2& end, const vec3& color)
{
	auto hex = createHex(color);
	drawLine(begin, end, hex);
}

void Renderer::drawLine(const vec2& begin, const vec2& end, unsigned long color)
{
	vec2 dt = end - begin;
	double length = dt.magnitude();
	vec2 addFactor = dt.normalize();

	dt.x = begin.x;
	dt.y = begin.y;

	for (double i = 0; i < length; i++)
	{
		setPixel_s({ dt.x, dt.y }, color);
		dt.x += addFactor.x;
		dt.y += addFactor.y;
	}
}

void Renderer::drawCircle(const vec2& pos, float radius, const vec3& color)
{
	unsigned long pxColor = createHex(color);
	drawCircle(pos, radius, pxColor);
}

void Renderer::plotCircle(const vec2& pos, float radius, const vec3& color)
{
	unsigned long pxColor = createHex(color);
	plotCircle(pos, radius, pxColor);
}

void Renderer::drawCircle(const vec2& pos, float radius, unsigned long color)
{
	int x = (int)-radius;
	int y = 0;
	int err = 2 - 2 * (int)radius;

	while (x < 0)
	{
		for (int i = (int)pos.x + x; i < (int)pos.x - x; i++)
		{
			setPixel_s(vec2((float)i, pos.y + y), color);
			setPixel_s(vec2((float)i, pos.y - y), color);
		}

		setPixel_s(vec2(pos.x - x, pos.y + y), color);
		setPixel_s(vec2(pos.x - y, pos.y - x), color);
		setPixel_s(vec2(pos.x + x, pos.y - y), color);
		setPixel_s(vec2(pos.x + y, pos.y + x), color);

		radius = (float)err;

		if (radius <= y) err += ++y * 2 + 1;
		if (radius > x || err > y) err += ++x * 2 + 1;
	}
}

void Renderer::plotCircle(const vec2& pos, float radius, unsigned long color)
{
	int x = (int)-radius;
	int y = 0;
	int err = 2 - 2 * (int)radius;

	while (x < 0)
	{
		setPixel_s(vec2(pos.x - x, pos.y + y), color);
		setPixel_s(vec2(pos.x - y, pos.y - x), color);
		setPixel_s(vec2(pos.x + x, pos.y - y), color);
		setPixel_s(vec2(pos.x + y, pos.y + x), color);

		radius = (float)err;

		if (radius <= y) err += ++y * 2 + 1;
		if (radius > x || err > y) err += ++x * 2 + 1;
	}
}

void Renderer::renderSprite(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size, const vec3& color)
{
	float posY = pos.y;

	for (int i = 0; i < sprite->m_Height; i++)
	{
		float posX = pos.x;
		for (int j = 0; j < sprite->m_Width; j++)
		{
			if (!(sprite->m_Buffer[i * sprite->m_Width + j] == vec3(-1.0f, -1.0f, -1.0f)))
				Renderer::drawQuad({ posX, posY }, size, sprite->m_Buffer[i * sprite->m_Width + j] * color);
			posX += size.x;
		}
		posY += size.y;
	}
}

void Renderer::drawText(const std::string& text, const vec2& pos, float size, const vec3& color)
{
	START_SCOPE_PROFILE("Text rendering");

	auto hexColor = createHex(color);
	vec2 Position = pos;
	
	for (int ch = 0; ch < text.size(); ch++)
	{
		char c = text[ch];
		if (c == ' ')
		{
			Position.x += 5;
			continue;
		}

		if (std::isupper(c))
			c = std::tolower(c);


		if (std::isdigit(c))
			drawNumber(c, Position, size, hexColor);
		else if (c >= 'a' && c <= 'z')
			drawChar(c, Position, size, hexColor);
		else if (Font::Exists(c))
			drawSymbol(c, Position, size, hexColor);


	}
}

void Renderer::drawText(const std::string& Text, int flags, float size, const vec3& color)
{
	vec2 Pos = {0.0f, 0.0f};

	auto textSize = Font::getTextWidth(Text);

	if (flags & Center)
	{
		Pos.x = m_Buffer->getWidth() / 2.0f - textSize / 2.0f;
		Pos.y = m_Buffer->getHeight() / 2.0f  - Font::m_GlyphHeight / 2.0f;
	}

	if (flags & Left)
		Pos.x = 0;

	if (flags & Right)
		Pos.x = m_Buffer->getWidth() - textSize;

	if (flags & Bottom)
		Pos.y = 0;

	if (flags & Top)
		Pos.y = m_Buffer->getHeight() - Font::m_GlyphHeight * size;

	drawText(Text, Pos, size, color);
}

void Renderer::drawChar(char c, vec2& pos, float size, unsigned int hexColor)
{
	int offset = c - 'a';

	float posY = pos.y;
	float posX = pos.x;

	for (int i = 0; i < Font::m_GlyphHeight; i++)
	{
		posX = pos.x;

		for (int j = offset * Font::m_GlyphWidth + 1; j < offset * Font::m_GlyphWidth + Font::getGlyphWidth(c) + 1; j++)
		{
			if (!(Font::m_FontSheet->m_Buffer[i * Font::m_FontSheet->m_Width + j] == vec3(-1.0f, -1.0f, -1.0f)))
				Renderer::drawQuad({ posX, posY }, { size, size }, hexColor);
			posX += size;
		}
		posY += size;
	}
	pos.x = posX + 1;
}

void Renderer::drawNumber(char n, vec2& pos, float size, unsigned int hexColor)
{
	int offset = n - '0';

	float posY = pos.y;
	float posX = pos.x;

	for (int i = 0; i < Font::m_GlyphHeight; i++)
	{
		posX = pos.x;

		for (int j = offset * Font::m_GlyphWidth + 1; j < offset * Font::m_GlyphWidth + Font::getGlyphWidth(n) + 1; j++)
		{
			if (!(Font::m_NumbersSheet->m_Buffer[i * Font::m_NumbersSheet->m_Width + j] == vec3(-1.0f, -1.0f, -1.0f)))
				Renderer::drawQuad({ posX, posY }, { size, size }, hexColor);
			posX += size;
		}
		posY += size;
	}
	pos.x = posX + 1;
}

void Renderer::drawSymbol(char s, vec2& pos, float size, unsigned int hexColor)
{
	int offset = Font::getSymbolOffset(s);

	float posY = pos.y;
	float posX = pos.x;

	for (int i = 0; i < Font::m_GlyphHeight; i++)
	{
		posX = pos.x;

		for (int j = offset * Font::m_GlyphWidth + 1; j < offset * Font::m_GlyphWidth + Font::getSymbolWidth(s) + 1; j++)
		{
			if (!(Font::m_SymbolsSheet->m_Buffer[i * Font::m_SymbolsSheet->m_Width + j] == vec3(-1.0f, -1.0f, -1.0f)))
				Renderer::drawQuad({ posX, posY }, { size, size }, hexColor);
			posX += size;
		}
		posY += size;
	}
	pos.x = posX + 1;
}
