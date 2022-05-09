#pragma once

#include "Utils/Maths.h"
#include "System/ScreenBuffer.h"
#include "Graphics/Sprite.h"
#include "Entity/Scene.h"
#include "Graphics/Font.h"

#include <memory>

enum TextAnchorFlags
{
	Center =		(1 << 0),
	Left =			(1 << 1),
	Right =			(1 << 2),
	Top =			(1 << 3),
	Bottom =		(1 << 4),
};

class Renderer
{
	friend class ScreenBuffer;

public:
	static void beginScene(const std::shared_ptr<Camera>& cam) { m_Camera = cam; }
	static void endScene();

	static void Init(std::shared_ptr<ScreenBuffer>& buffer);

	static void Clear(float r, float g, float b);

	static void drawQuad(const vec2& pos, const vec2& size, const vec3& color);
	static void drawQuad(const vec2& pos, const vec2& size, unsigned long color);

	static void plotQuad(const vec2& pos, const vec2& size, const vec3& color);
	static void plotQuad(const vec2& pos, const vec2& size, unsigned long color);

	static void drawLine(const vec2& begin, const vec2& end, const vec3& color);
	static void drawLine(const vec2& begin, const vec2& end, unsigned long color);

	static void drawCircle(const vec2& pos, float radius, const vec3& color);
	static void plotCircle(const vec2& pos, float radius, const vec3& color);
	
	static void drawCircle(const vec2& pos, float radius, unsigned long color);
	static void plotCircle(const vec2& pos, float radius, unsigned long color);

	static void renderSprite(const std::shared_ptr<Sprite>& sprite, const vec2& pos, const vec2& size, const vec3& color = { 1.0f, 1.0f, 1.0f });

	static void setPixel(const vec2& pos, const vec3& color);
	static void setPixel_s(const vec2& pos, const vec3& color);
	static void setPixel(const vec2& pos, unsigned long hexColor);
	static void setPixel_s(const vec2& pos, unsigned long hexColor);

	static void renderScene(const std::shared_ptr<Scene>& scene);

	static void setDepthPixel(int column, float depth);
	static float getPixelDepth(int column);

	static bool checkPixel(const vec2& pos);

	static void drawText(const std::string& text, const vec2& pos, float size, const vec3& color);
	static void drawText(const std::string& text, int flags, float size, const vec3& color);

private:
	static std::shared_ptr<ScreenBuffer> m_Buffer;
	static std::shared_ptr<Camera> m_Camera;
	static uint32* m_BuffersBuffer; // ;-?
	static float* m_DepthBuffer;

private:
	static void drawChar(char c, vec2& pos, float size, unsigned int color);
	static void drawNumber(char n, vec2& pos, float size, unsigned int color);
	static void drawSymbol(char s, vec2& pos, float size, unsigned int color);
};