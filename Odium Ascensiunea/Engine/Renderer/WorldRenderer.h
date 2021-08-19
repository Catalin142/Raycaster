#pragma once
#include "Graphics/Sprite.h"

#include "Utils/Types.h"
#include "Utils/Maths.h"

#include "Graphics/Sprite.h"
#include "ScreenBuffer.h"

#include "Camera.h"
#include "Utils/Map.h"

class WorldRenderer
{
public:
	static void Render(std::shared_ptr<ScreenBuffer>& buffer, std::shared_ptr<Camera>& cam);

private:
	static std::shared_ptr<Map> m_Map;

	static void setIntensity(float intensity) { m_UseIntensity = true; m_ShadeIntensity = intensity; }
	static void setIntensity(bool state) { m_UseIntensity = state; }

private:
	WorldRenderer() = default;
	~WorldRenderer() = default;

	static unsigned long samplePixel(const vec2& loc, const vec2& pixel);

	vec3 m_CeilColor;
	std::shared_ptr<Sprite> m_CeilTexture;

	static float m_ShadeIntensity;
	static bool m_UseIntensity;
};