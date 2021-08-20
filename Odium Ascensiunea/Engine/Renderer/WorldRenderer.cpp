#include "Core/RaycastPCH.h"
#include "WorldRenderer.h"

#include "Utils/Color.h"
#include "Utils/Map.h"
#include "Renderer.h"
#include "Utils/Raycaster.h"

std::shared_ptr<Map> WorldRenderer::m_Map;

float WorldRenderer::m_ShadeIntensity = 1.0f;
bool WorldRenderer::m_UseIntensity = false;

unsigned long WorldRenderer::m_CeilColor = 0x0000000;
std::shared_ptr<Sprite> WorldRenderer::m_CeilTexture;

vec3 WorldRenderer::Gradient::m_StartColor;
vec3 WorldRenderer::Gradient::m_EndColor;
float WorldRenderer::Gradient::m_Intensity;

WorldRenderer::Gradient WorldRenderer::m_CeilGradient;

CeilShadingMode WorldRenderer::m_CeilMode = CeilShadingMode::SOLID;

void WorldRenderer::Render(std::shared_ptr<ScreenBuffer>& buffer, std::shared_ptr<Camera>& cam)
{
	m_Map = Map::Get();
	vec2 wallSize;
	vec2 wallPos;

	vec3 Color = { 0.0f, 0.0f, 0.0f };

	vec2 BufferDim = { (float)buffer->getWidth(), (float)buffer->getHeight() };

	for (int x = 0; x < BufferDim.x; x++)
	{
		float rayAng = (cam->m_CameraAngle - degToRad(cam->m_FOV) / 2.0f) + ((float)x / BufferDim.x) * degToRad(cam->m_FOV);

		auto res = castRay(cam, rayAng);

		wallSize = { 1.0f, (1600.0f / 900.0f) * BufferDim.y / res.Length };
		wallPos = { (float)x, BufferDim.y / 2.0f - wallSize.y / 2.0f };

		vec2 rayDir = { cos(rayAng), sin(rayAng) };

		float fishEyeCorrection = (1600.0f / 900.0f) / std::cos(rayAng - cam->m_CameraAngle);

		auto& wallSpr = m_Map->getSprite(res.Symbol);
		vec3 Shade = { 1.0f, 1.0f, 1.0f };
		for (int y = 0; y < BufferDim.y; y++)
		{
			// podea
			if (y <= (int)wallPos.y)
			{
				float Plane = (BufferDim.y / 2.0f) / ((BufferDim.y / 2.0f) - float(y));

				if (m_UseIntensity == true)
					Shade = vec3(1.0f, 1.0f, 1.0f) * (m_ShadeIntensity / Plane);

				vec2 planePoint = cam->m_Position + rayDir * Plane * fishEyeCorrection;
				vec2 pixel;

				pixel.x = planePoint.x - (int)planePoint.x;
				pixel.y = planePoint.y - (int)planePoint.y;

				Color = samplePixel(planePoint, pixel);
			}

			// pereti
			else if (y > (int)wallPos.y && y <= (int)wallPos.y + wallSize.y)
			{
				if (m_UseIntensity == true)
					if (res.Length > 0.5f)
						Shade = vec3(1.0f, 1.0f, 1.0f) * (m_ShadeIntensity / res.Length);
				Color = wallSpr->getPixelColor(res.HitPosition, (y - wallPos.y) / (int)(wallSize.y));
			}

			// tavan
			else
			{
				float Plane = (BufferDim.y / 2.0f) / ((BufferDim.y / 2.0f) - float(y));

				if (m_UseIntensity == true)
					Shade = vec3(1.0f, 1.0f, 1.0f) * (m_ShadeIntensity / (-Plane));

				switch (m_CeilMode)
				{
				case CeilShadingMode::SOLID:
					Color = { 1.0f, 1.0f, 1.0f };
					break;

				case CeilShadingMode::TEXTURE:
					vec2 planePoint = cam->m_Position - rayDir * Plane * fishEyeCorrection;
					vec2 pixel;

					pixel.x = planePoint.x - (int)planePoint.x;
					pixel.y = planePoint.y - (int)planePoint.y;

					Color = m_CeilTexture->getPixelColor(pixel.x, pixel.y);
					break;

				case CeilShadingMode::LERP:
					vec3 col = lerp(m_CeilGradient.m_StartColor, m_CeilGradient.m_EndColor, m_CeilGradient.m_Intensity / y);
					Color = col;
					break;
				}
			}

			if (m_UseIntensity == false)
				Renderer::setPixel({ (float)x, (float)y }, Color);
			else // aici merge ff prost ca il fac in rgb dupa iara in hex pt fiecare pixel si ia prea mult
				Renderer::setPixel({ (float)x, (float)y }, Color * Shade);
		}

	}
	Map::Get()->updatePlayerPosition(cam->m_Position);
}

// merge ff prost in debug mode da in release am 400+ fps
vec3& WorldRenderer::samplePixel(const vec2& loc, const vec2& pixel)
{
	return m_Map->getSprite(m_Map->m_Map[(int)loc.y * m_Map->m_Width + (int)loc.x])->getPixelColor(pixel.x, pixel.y);
}

