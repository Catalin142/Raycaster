#pragma once

#include "Utils/Maths.h"
#include "System/ScreenBuffer.h"
#include "Graphics/Sprite.h"
#include "Entity/Scene.h"
#include "Graphics/Font.h"

#include <memory>

enum TextAnchorFlags
{
	TextCenter =		(1 << 0),
	TextLeft =			(1 << 1),
	TextRight =			(1 << 2),
	TextTop =			(1 << 3),
	TextBottom =		(1 << 4),
};

class Renderer
{
	friend class ScreenBuffer;

public:
	static void Init(std::shared_ptr<ScreenBuffer>& buffer);

	static void drawQuad(const vec2& pos, const vec2& size, const vec3& color);
	static void drawQuad(const vec2& pos, const vec2& size, unsigned long color);

	static void drawLine(const vec2& begin, const vec2& end, const vec3& color);

	static void drawCircle(const vec2& pos, float radius, const vec3& color);
	static void plotCircle(const vec2& pos, float radius, const vec3& color);
	
	static void drawCircle(const vec2& pos, float radius, unsigned long color);
	static void plotCircle(const vec2& pos, float radius, unsigned long color);

	static void renderSprite(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size);

	static void setPixel(const vec2& pos, const vec3& color);
	static void setPixel_s(const vec2& pos, const vec3& color);
	static void setPixel(const vec2& pos, unsigned long hexColor);
	static void setPixel_s(const vec2& pos, unsigned long hexColor);

	static void renderScene(const std::shared_ptr<Scene>& scene);

	static void setDepthPixel(int column, float depth);
	static float getPixelDepth(int column);

	static bool checkPixel(const vec2& pos);

	static void drawText(const std::string& text, const std::shared_ptr<Font>& font, const vec2& pos, float size, const vec3& color, float space = 1.0f);
	static void drawText(const std::string& text, const std::shared_ptr<Font>& font, int flags, float size, const vec3& color, float space = 1.0f);

private:
	static std::shared_ptr<ScreenBuffer> m_Buffer;
	static uint32* m_BuffersBuffer; // ;-?
	static float* m_DepthBuffer;
};