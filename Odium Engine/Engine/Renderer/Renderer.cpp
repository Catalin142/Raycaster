#include "Core/RaycastPCH.h"
#include "Renderer.h"
#include "Utils/Color.h"

std::shared_ptr<ScreenBuffer> Renderer::m_Buffer;
uint32* Renderer::m_BuffersBuffer;
float* Renderer::m_DepthBuffer;

void Renderer::Init(std::shared_ptr<ScreenBuffer>& buffer)
{
	m_Buffer = buffer;
	(uint32*)m_BuffersBuffer = (uint32*)m_Buffer->m_MemoryBuffer;
	m_DepthBuffer = m_Buffer->m_DepthBuffer;
}

void Renderer::drawQuad(const vec2& pos, const vec2& size, unsigned long color)
{
	float startY = Clamp(pos.y, 0, m_Buffer->m_Height - 1.0f);
	float endY = Clamp(pos.y + size.y, 0, m_Buffer->m_Height - 1.0f);

	float startX = Clamp(pos.x, 0, m_Buffer->m_Width - 1.0f);
	float endX = Clamp(pos.x + size.x, 0, m_Buffer->m_Width - 1.0f);

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

void Renderer::setPixel(const vec2& pos, const vec3& color)
{
	int pixel = (int)pos.y * m_Buffer->m_Width + (int)pos.x;
	*(m_BuffersBuffer + pixel) = createHex(color.r * 255, color.g * 255, color.b * 255);
}

void Renderer::setPixel_s(const vec2& pos, const vec3& color)
{
	if (checkPixel(pos))
		return;
	setPixel(pos, color);
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
			ent->onDraw();
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
	vec2 dt = end - begin;
	double length = dt.magnitude();
	vec2 addFactor = dt.normalize();

	dt.x = begin.x;
	dt.y = begin.y;

	for (double i = 0; i < length; i ++)
	{
		setPixel({ dt.x, dt.y }, color);
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

void Renderer::renderSprite(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size)
{
	float posY = pos.y;
	for (int i = 0; i < sprite->m_Height; i++)
	{
		float posX = pos.x;
		for (int j = 0; j < sprite->m_Width; j++)
		{
			if (!(sprite->m_Buffer[i * sprite->m_Width + j] == vec3(-1.0f, -1.0f, -1.0f)))
				Renderer::drawQuad({ posX, posY }, size, sprite->m_Buffer[i * sprite->m_Width + j]);
			posX += size.x;
		}
		posY += size.y;
	}
}
