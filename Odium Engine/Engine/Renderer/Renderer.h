#pragma once

#include "Utils/Maths.h"
#include "System/ScreenBuffer.h"
#include "Graphics/Sprite.h"
#include "Entity/Scene.h"

#include <memory>

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

private:
	static std::shared_ptr<ScreenBuffer> m_Buffer;
	static uint32* m_BuffersBuffer; // ;-?
	static float* m_DepthBuffer;
};