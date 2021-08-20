#pragma once
#include "Graphics/Sprite.h"

#include "Utils/Types.h"
#include "Utils/Maths.h"

#include "Graphics/Sprite.h"
#include "ScreenBuffer.h"

#include "Camera.h"
#include "Utils/Map.h"

#include "Utils/Color.h"

enum class CeilShadingMode : short
{
	LERP,
	SOLID,
	TEXTURE,
};

enum class WorldLightMode : short
{
	NORMAL,
	DARK, // in release ( ~325 fps ) 
};

class WorldRenderer
{
public:
	static void Render(std::shared_ptr<ScreenBuffer>& buffer, std::shared_ptr<Camera>& cam);

	static void setIntensity(float intensity) { m_UseIntensity = true; m_ShadeIntensity = intensity; }
	static void setIntensity(bool state) { m_UseIntensity = state; }

	static void setCeilTexture(const std::shared_ptr<Sprite>& tex) { m_CeilTexture = tex; m_CeilMode = CeilShadingMode::TEXTURE; }
	static void setCeilColor(const vec3& color) { m_CeilColor = createHex(color.x * 255, color.y * 255, color.z * 255); m_CeilMode = CeilShadingMode::SOLID; }
	static void setCeilGradient(const vec3& from, const vec3& to, float intensity) {
		m_CeilGradient.m_StartColor = from;
		m_CeilGradient.m_EndColor = to;
		m_CeilGradient.m_Intensity = intensity;
		m_CeilMode = CeilShadingMode::LERP;
	}

private:
	static std::shared_ptr<Map> m_Map;

	static vec3& samplePixel(const vec2& loc, const vec2& pixel);

	static unsigned long m_CeilColor;
	static std::shared_ptr<Sprite> m_CeilTexture;

	struct Gradient
	{
		static vec3 m_StartColor;
		static vec3 m_EndColor;
		static float m_Intensity;
	} static m_CeilGradient;

	static CeilShadingMode m_CeilMode;

	static float m_ShadeIntensity;
	static bool m_UseIntensity;

private:
	WorldRenderer() = default;
	~WorldRenderer() = default;
};