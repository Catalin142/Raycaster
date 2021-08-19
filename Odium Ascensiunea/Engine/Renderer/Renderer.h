#pragma once

#include "../Utils/Maths.h"
#include "../ScreenBuffer.h"
#include "../Graphics/Sprite.h"

#include <memory>

class Renderer
{
	friend class ScreenBuffer;

public:
	static void Init(std::shared_ptr<ScreenBuffer>& buffer);

	static void drawQuad(const vec2& pos, const vec2& size, const vec3& color);
	static void drawQuad(const vec2& pos, const vec2& size, unsigned long color);

	static void drawLine(const vec2& begin, const vec2& end, const vec3& color);

	static void renderSprite(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size);

	static void setPixel(const vec2& pos, const vec3& color); // nu mai verific nimic aici
	static void setPixel(const vec2& pos, unsigned long hexColor);
	
	static bool checkPixel(const vec2& pos);

private:
	static std::shared_ptr<ScreenBuffer> m_Buffer;
	static uint32* m_BuffersBuffer; // ;-?
};