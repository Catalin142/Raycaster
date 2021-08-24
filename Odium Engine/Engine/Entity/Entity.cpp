#include "Core/RaycastPCH.h"
#include "Entity.h"

#include "Renderer/Renderer.h"
#include "Renderer/WorldRenderer.h"

#include "System/Application.h"

Entity::Entity(const std::string& filepath)
{
	setSprite(filepath);
}

Entity::Entity(const std::shared_ptr<Sprite>& spr)
{
	m_Sprite = spr;
}

void Entity::onDraw()
{
	auto m_Camera = Application::Get()->m_Camera;
	auto m_Buffer = Application::Get()->m_Buffer;

	vec2 Dist;
	Dist.x = m_Position.x - m_Camera->m_Position.x;
	Dist.y = m_Position.y - m_Camera->m_Position.y;

	float distFromPlayer = Dist.magnitude();
	vec2 pDirection = { cos(m_Camera->m_CameraAngle), sin(m_Camera->m_CameraAngle) };
	float objAng = atan2f(pDirection.x, pDirection.y) - atan2f(Dist.x, Dist.y);

	if (objAng < -PI)
		objAng += 2.0f * PI;
	if (objAng > PI)
		objAng -= 2.0f * PI;

	if (fabs(objAng) < degToRad(m_Camera->m_FOV) / 2.0f && distFromPlayer > 1.0f)
	{
		float objHeight = (1600.0f / 900.0f) * m_Buffer->getHeight() / distFromPlayer;
		float objFloor = m_Buffer->getHeight() / 2.0f - objHeight / 2.0f;
		float objCeil = m_Buffer->getHeight() - objFloor;
		float objWidth = objHeight / m_Sprite->getAspectRatio();
		float objMiddle = (0.5f * (objAng / (degToRad(m_Camera->m_FOV) / 2.0f)) + 0.5f) * (float)m_Buffer->getWidth();

		for (int x = 0; x < objWidth; x++)
			for (int y = 0; y < objHeight; y++)
			{
				int objColumn = (int)(objMiddle + x - (objWidth / 2.0f));

				if (distFromPlayer <= Renderer::getPixelDepth(objColumn))
				{
					vec2 samplePoint = { (float)x / objWidth, (float)y / objHeight };
					vec3 color = m_Sprite->getPixelColor(samplePoint.x, samplePoint.y);
					if (color == vec3(-1.0f, -1.0f, -1.0f))
						continue;

					if (WorldRenderer::m_UseIntensity && m_ApplyGlobalIllumination)
						color = color * (WorldRenderer::m_GlobalIlluminationIntensity / distFromPlayer);

					if (m_UseObjIntensity)
						color = color * (m_ObjectIntensity / distFromPlayer);

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

	m_Sprite = std::make_shared<Sprite>(filepath);
}
