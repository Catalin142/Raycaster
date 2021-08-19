#include "Core/RaycastPCH.h"
#include "Renderer.h"
#include "Utils/Color.h"

std::shared_ptr<ScreenBuffer> Renderer::m_Buffer;
uint32* Renderer::m_BuffersBuffer;

void Renderer::Init(std::shared_ptr<ScreenBuffer>& buffer)
{
	m_Buffer = buffer;
	(uint32*)m_BuffersBuffer = (uint32*)m_Buffer->getBuffer();
}

void Renderer::drawQuad(const vec2& pos, const vec2& size, unsigned long color)
{
	float startY = Clamp(pos.y, 0, m_Buffer->m_Height);
	float endY = Clamp(pos.y + size.y, 0, m_Buffer->m_Height);

	float startX = Clamp(pos.x, 0, m_Buffer->m_Width);
	float endX = Clamp(pos.x + size.x, 0, m_Buffer->m_Width);

	uint32* pixel;
	for (int y = startY; y < endY; y++)
	{
		pixel = (uint32*)m_BuffersBuffer + (int)startX + (int)y * m_Buffer->m_Width;
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
	int pixel = pos.y * m_Buffer->m_Width + pos.x;
	*(m_BuffersBuffer + pixel) = createHex(color.r * 255, color.g * 255, color.b * 255);
}

void Renderer::setPixel(const vec2& pos, unsigned long hexColor)
{
	int pixel = pos.y * m_Buffer->m_Width + pos.x;
	*(m_BuffersBuffer + pixel) = hexColor;
}

bool Renderer::checkPixel(const vec2& pos)
{
	return (pos.x > m_Buffer->m_Width || pos.y > m_Buffer->m_Height - 1.0f || pos.x < 0 || pos.y < 0);
}

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

void Renderer::renderSprite(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size)
{
	float posY = pos.y + size.y * sprite->m_Height;
	for (int i = 0; i < sprite->m_Height; i++)
	{
		float posX = pos.x;
		for (int j = 0; j < sprite->m_Width; j++)
		{
			if (sprite->m_Buffer[i * sprite->m_Width + j] != -1)
				Renderer::drawQuad({ posX, posY }, size, sprite->m_Buffer[i * sprite->m_Width + j]);
			posX += size.x;
		}
		posY -= size.y;
	}
}
