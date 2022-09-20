#include "Core/RaycastPCH.h"
#include "Entity.h"

#include "Renderer/Renderer.h"
#include "Renderer/WorldRenderer.h"

#include "Tools/Benchmark.h"

#include "System/Application.h"

Entity::Entity(const std::string& filepath)
{
	setSprite(filepath);
}

Entity::Entity(const std::shared_ptr<Sprite>& spr)
{
	m_Sprite = spr;
}

void Entity::onDraw(const std::shared_ptr<Scene>& scn)
{
	START_SCOPE_PROFILE("Entity render");

	auto& cam = scn->getCamera();

	auto& m_Buffer = Application::Get()->m_Buffer;

	vec2 Dist;
	Dist.x = m_Position.x - cam->m_Position.x;
	Dist.y = m_Position.y - cam->m_Position.y;

	float distFromPlayer = Dist.magnitude();
	vec2 pDirection = { cos(cam->m_CameraAngle), sin(cam->m_CameraAngle) };
	float objAng = atan2f(pDirection.x, pDirection.y) - atan2f(Dist.x, Dist.y);

	if (objAng < -PI)
		objAng += 2.0f * PI;
	if (objAng > PI)
		objAng -= 2.0f * PI;

	if (fabs(objAng) < degToRad(cam->m_FOV) / 2.0f && distFromPlayer > 1.0f)
	{
		float windowWidth = (float)Application::Get()->getBuffer()->getWidth();
		float windowHeight = (float)Application::Get()->getBuffer()->getHeight();
		float objHeight = (windowWidth / windowHeight) * m_Buffer->getHeight() / distFromPlayer * m_Height;
		float objFloor = m_Buffer->getHeight() / 2.0f - (objHeight / 2.0f / m_Height);
		float objCeil = m_Buffer->getHeight() - objFloor;
		float objWidth = objHeight / m_Sprite->getAspectRatio() * m_Width;
		float objMiddle = (0.5f * (objAng / (degToRad(cam->m_FOV) / 2.0f)) + 0.5f) * (float)m_Buffer->getWidth();

		for (int x = 0; x < objWidth; x++)
			for (int y = 0; y < objHeight; y++)
			{
				int objColumn = (int)(objMiddle + x - (objWidth / 2.0f));

				vec3 shade = { 1.0f, 1.0f, 1.0f };
				if (distFromPlayer <= Renderer::getPixelDepth(objColumn))
				{
					vec2 samplePoint = { (float)x / objWidth, (float)y / objHeight };
					vec3 color = m_Sprite->getPixelColor(samplePoint.x, samplePoint.y);
					if (color == vec3(-1.0f, -1.0f, -1.0f))
						continue;

					bool light = false;
					vec2 planePoint = m_Position + samplePoint;
					float intensity = 1.0f;
					
					if (WorldRenderer::m_UseIntensity && m_ApplyGlobalIllumination)
						shade = vec3(1.0f, 1.0f, 1.0f) * (WorldRenderer::m_GlobalIlluminationIntensity / distFromPlayer);

					for (const auto& l : scn->getLights())
					{
						float d = (planePoint.x - l->light_source.x) * (planePoint.x - l->light_source.x) +
							(planePoint.y - l->light_source.y) * (planePoint.y - l->light_source.y);
						if (d < l->light_radius * l->light_radius)
						{
							light = true;
							intensity = l->light_intensity * (1.0f - d / (l->light_radius * l->light_radius));
							color = { (1.0f - intensity) * color.r + (intensity * l->light_color.r),
							(1.0f - intensity) * color.g + (intensity * l->light_color.g), (1.0f - intensity) * color.b + (intensity * l->light_color.b) };

							shade = { (1.0f - intensity) * shade.r + (intensity * l->light_color.r),
								(1.0f - intensity) * shade.g + (intensity * l->light_color.g), (1.0f - intensity) * shade.b + (intensity * l->light_color.b) };
						}
					}

					color = color * shade;
						
					if (m_UseObjIntensity)
						color = color * (m_ObjectIntensity / distFromPlayer);
					

					if (WorldRenderer::m_Fog)
					{
						vec3 Fog = vec3(1.0f, 1.0f, 1.0f) * distFromPlayer * WorldRenderer::m_FogIntensity;
						Fog = Fog / 20.0f;
						color = { (1.0f - Fog.r) * color.r + (Fog.r),
							(1.0f - Fog.g) * color.g + (Fog.g), (1.0f - Fog.b) * color.b + (Fog.b) };
					}

					Renderer::setPixel_s(vec2((int)objColumn, (int)objFloor + y), color);
					Renderer::setDepthPixel(objColumn, distFromPlayer);
				}
			}
	}
}

void Entity::setSprite(const std::string& filepath)
{
	if (m_Sprite)
	{
		m_Sprite.reset();
		m_Sprite = nullptr;
	}

	m_Sprite = SpriteManager::loadSprite(filepath);
}
