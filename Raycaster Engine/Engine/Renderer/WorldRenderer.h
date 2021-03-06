#pragma once
#include "Graphics/Sprite.h"

#include "Utils/Types.h"
#include "Utils/Maths.h"

#include "Graphics/Sprite.h"
#include "System/ScreenBuffer.h"

#include "Camera.h"
#include "Utils/Map.h"

#include "Utils/Color.h"

enum class ShadingMode : short
{
	LERP,
	SOLID,
	TEXTURE,
};

class WorldRenderer
{
	friend class Entity;

public:
	static void Render(const std::shared_ptr<ScreenBuffer>& buffer, const std::shared_ptr<Camera>& cam);

	static void setGlobalIlluminationIntensity(float intensity) { m_UseIntensity = true; m_GlobalIlluminationIntensity = intensity; }
	static void setGlobalIlluminationIntensity(bool state) { m_UseIntensity = state; }

	static void setCeilTexture(const std::shared_ptr<Sprite>& tex) { m_CeilTexture = tex; m_CeilMode = ShadingMode::TEXTURE; }
	static void setCeilColor(const vec3& color) { m_CeilColor = color; m_CeilMode = ShadingMode::SOLID; }
	static void setCeilGradient(const vec3& from, const vec3& to, float intensity) {
		m_CeilGradient.m_StartColor = from;
		m_CeilGradient.m_EndColor = to;
		m_CeilGradient.m_Scale = intensity;
		m_CeilMode = ShadingMode::LERP;
	}

	static void setFloorColor(const vec3& color) { m_FloorColor = color; m_FloorMode = ShadingMode::SOLID; }
	static void setFloorGradient(const vec3& from, const vec3& to, float intensity) {
		m_FloorGradient.m_StartColor = from;
		m_FloorGradient.m_EndColor = to;
		m_FloorGradient.m_Scale = intensity;
		m_FloorMode = ShadingMode::LERP;
	}

private:
	static std::shared_ptr<Map> m_Map;

	static const vec3& samplePixel(const vec2& loc, const vec2& pixel);

	static vec3 m_CeilColor;
	static vec3 m_FloorColor;
	static std::shared_ptr<Sprite> m_CeilTexture;

	struct Gradient
	{
		static vec3 m_StartColor;
		static vec3 m_EndColor;
		static float m_Scale;
	} static m_CeilGradient, m_FloorGradient;

	static ShadingMode m_CeilMode;
	static ShadingMode m_FloorMode;

	static float m_GlobalIlluminationIntensity;
	static bool m_UseIntensity;

private:
	WorldRenderer() = default;
	~WorldRenderer() = default;
};