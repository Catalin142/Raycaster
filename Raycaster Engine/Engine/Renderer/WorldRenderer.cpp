#include "Core/RaycastPCH.h"
#include "WorldRenderer.h"

#include "Utils/Color.h"
#include "Utils/Map.h"
#include "Renderer.h"
#include "Utils/Raycaster.h"
#include "Tools/Benchmark.h"

#include <chrono>
#include <unordered_map>

std::shared_ptr<Scene> WorldRenderer::m_Scene;

float WorldRenderer::m_GlobalIlluminationIntensity = 1.0f;
bool WorldRenderer::m_UseIntensity = false;

vec3 WorldRenderer::m_CeilColor = {0.0f, 0.0f, 0.0f};
vec3 WorldRenderer::m_FloorColor = { 0.0f, 0.0f, 0.0f };
std::shared_ptr<Sprite> WorldRenderer::m_CeilTexture;

vec3 WorldRenderer::Gradient::m_StartColor;
vec3 WorldRenderer::Gradient::m_EndColor;
float WorldRenderer::Gradient::m_Scale;

WorldRenderer::Gradient WorldRenderer::m_CeilGradient;
WorldRenderer::Gradient WorldRenderer::m_FloorGradient;

ShadingMode WorldRenderer::m_CeilMode = ShadingMode::SOLID;
ShadingMode WorldRenderer::m_FloorMode = ShadingMode::TEXTURE;

RenderThread* WorldRenderer::m_Threads[5];
std::mutex WorldRenderer::m_ThreadsMutex;

bool WorldRenderer::m_LSD = false;

bool WorldRenderer::m_Fog = false;
float WorldRenderer::m_FogIntensity = 1.0f;

void WorldRenderer::Init()
{
	int slice_width = Application::Get()->getBuffer()->getWidth() / 5;
	for (int i = 0; i < 5; i++)
	{
		m_Threads[i] = new RenderThread();
		m_Threads[i]->s_WorkerThread = std::thread(threadRender, m_Threads[i], slice_width * i, slice_width * (i + 1));
	}
}

void WorldRenderer::Destroy()
{
	for (int i = 0; i < 5; i++)
	{
		m_Threads[i]->s_Quit = true;
		m_Threads[i]->s_WorkerThread.join();
		delete m_Threads[i];
	}
}

void WorldRenderer::Render(const std::shared_ptr<Scene>& scn)
{
	m_Scene = scn;
	START_SCOPE_PROFILE("Render");
	for (int i = 0; i < 5; i++)
		m_Threads[i]->s_isRunning = true;

	for (int i = 0; i < 5; i++)
	{
		std::unique_lock<std::mutex> mutex(m_Threads[i]->s_ThreadMutex);
		m_Threads[i]->s_Condition.wait(mutex, [&]() -> bool { 
			return m_Threads[i]->s_isRunning == false; 
			});
	}

	m_Scene->m_Map->updatePlayerPosition(m_Scene->getCamera()->m_Position);
}

// merge ff prost in debug mode da in release am 400+ fps
const vec3& WorldRenderer::samplePixel(const vec2& loc, const vec2& pixel)
{
	return m_Scene->m_Map->getSprite(m_Scene->m_Map->m_Buffer[(int)loc.y * m_Scene->m_Map->m_Width + (int)loc.x])->getPixelColor(pixel.x, pixel.y);
}

void WorldRenderer::threadRender(RenderThread* thread, uint32 minx, uint32 maxx)
{
	while (true)
	{
		if (thread->s_isRunning)
		{
			START_SCOPE_PROFILE("Raycasting Render");
			vec2 buffer_size = { (float)Application::Get()->getBuffer()->getWidth(), (float)Application::Get()->getBuffer()->getHeight() };
			float aspect_ratio = buffer_size.x / buffer_size.y;
			for (int x = minx; x < maxx; x++)
			{
				float rayAng = (m_Scene->getCamera()->m_CameraAngle - degToRad(m_Scene->getCamera()->m_FOV) / 2.0f) + 
					((float)x / buffer_size.x) * degToRad(m_Scene->getCamera()->m_FOV);

				RaycastResult res = castRay(m_Scene, rayAng);

				vec2 wallSize = { 1.0f, aspect_ratio * buffer_size.y / res.Length };
				vec2 wallPos = { (float)x, buffer_size.y / 2.0f - wallSize.y / 2.0f };

				vec2 rayDir = { cos(rayAng), sin(rayAng) };

				float fishEyeCorrection = aspect_ratio / std::cos(rayAng - m_Scene->getCamera()->m_CameraAngle);

				auto& wallSpr = m_Scene->m_Map->getSprite(res.Symbol);
				vec3 Shade = { 1.0f, 1.0f, 1.0f };
				vec3 Fog = { 1.0f, 1.0f, 1.0f };
				vec3 Color = { 0.0f, 0.0f, 0.0f };

				for (int y = 0; y < buffer_size.y; y++)
				{
					float intensity = 1.0f;
					// podea
					if (y <= (int)wallPos.y)
					{
						float Plane = (buffer_size.y / 2.0f) / ((buffer_size.y / 2.0f) - float(y));

						if (m_UseIntensity)
							Shade = vec3(1.0f, 1.0f, 1.0f) * (m_GlobalIlluminationIntensity / Plane);

						if (m_Fog)
							Fog = vec3(1.8f, 1.8f, 1.8f) * (Plane)*m_FogIntensity;

						vec2 planePoint = m_Scene->getCamera()->m_Position + rayDir * Plane * fishEyeCorrection;
						switch (m_FloorMode)
						{
						case ShadingMode::SOLID:
							Color = m_FloorColor;
							break;

						case ShadingMode::TEXTURE:
							vec2 pixel;

							pixel.x = planePoint.x - (int)planePoint.x;
							pixel.y = planePoint.y - (int)planePoint.y;

							Color = samplePixel(planePoint, pixel);
							break;

						case ShadingMode::LERP:
							vec3 col = lerp(m_FloorGradient.m_StartColor, m_FloorGradient.m_EndColor, m_FloorGradient.m_Scale / (buffer_size.y - y));
							Color = col;
							break;
						}

						for (const auto& l : m_Scene->m_Lights)
						{
							float d = (planePoint.x - l->light_source.x) * (planePoint.x - l->light_source.x) +
								(planePoint.y - l->light_source.y) * (planePoint.y - l->light_source.y);
							if (d < l->light_radius * l->light_radius)
							{
								intensity = l->light_intensity * (1.0f - d / (l->light_radius * l->light_radius));
								Color = { (1.0f - intensity) * Color.r + (intensity * l->light_color.r),
								(1.0f - intensity) * Color.g + (intensity * l->light_color.g), (1.0f - intensity) * Color.b + (intensity * l->light_color.b) };

								Shade = { (1.0f - intensity) * Shade.r + (intensity * l->light_color.r),
								(1.0f - intensity) * Shade.g + (intensity * l->light_color.g), (1.0f - intensity) * Shade.b + (intensity * l->light_color.b) };
							}
						}
					}

					// pereti
					else if (y > (int)wallPos.y && y <= (int)wallPos.y + wallSize.y)
					{
						res.Length = std::max(1.0f, res.Length);
						if (m_UseIntensity)
							Shade = vec3(1.0f, 1.0f, 1.0f) * (m_GlobalIlluminationIntensity / res.Length);

						Color = wallSpr->getPixelColor(res.HitPosition, (y - wallPos.y) / (int)(wallSize.y));

						Renderer::setDepthPixel(x, res.Depth);
						for (const auto& l : m_Scene->m_Lights)
						{
							float d = (res.Location.x - l->light_source.x) * (res.Location.x - l->light_source.x) +
								(res.Location.y - l->light_source.y) * (res.Location.y - l->light_source.y);
							if (d < l->light_radius * l->light_radius)
							{
								intensity = l->light_intensity * (1.0f - d / (l->light_radius * l->light_radius));
								Color = { (1.0f - intensity) * Color.r + (intensity * l->light_color.r),
								(1.0f - intensity) * Color.g + (intensity * l->light_color.g), (1.0f - intensity) * Color.b + (intensity * l->light_color.b) };

								Shade = { (1.0f - intensity) * Shade.r + (intensity * l->light_color.r),
								(1.0f - intensity) * Shade.g + (intensity * l->light_color.g), (1.0f - intensity) * Shade.b + (intensity * l->light_color.b) };
							}
						}

						if (m_Fog)
							Fog = vec3(1.0f, 1.0f, 1.0f) * res.Length * m_FogIntensity;

					}

					// tavan
					else
					{
						float Plane = (buffer_size.y / 2.0f) / ((buffer_size.y / 2.0f) - float(y));

						if (m_UseIntensity)
							Shade = vec3(1.0f, 1.0f, 1.0f) * (m_GlobalIlluminationIntensity / (-Plane));

						if (m_Fog)
							Fog = vec3(1.8f, 1.8f, 1.8f) * (-Plane) * m_FogIntensity;
						vec2 planePoint = m_Scene->getCamera()->m_Position - rayDir * Plane * fishEyeCorrection;

						switch (m_CeilMode)
						{
						case ShadingMode::SOLID:
							Color = m_CeilColor;
							break;

						case ShadingMode::TEXTURE:
							vec2 pixel;

							pixel.x = planePoint.x - (int)planePoint.x;
							pixel.y = planePoint.y - (int)planePoint.y;

							Color = m_CeilTexture->getPixelColor(pixel.x, pixel.y);
							break;

						case ShadingMode::LERP:
							vec3 col = lerp(m_CeilGradient.m_StartColor, m_CeilGradient.m_EndColor, m_CeilGradient.m_Scale / y);
							Color = col;
							break;
						}

						for (const auto& l : m_Scene->m_Lights)
						{
							float d = (planePoint.x - l->light_source.x) * (planePoint.x - l->light_source.x) +
								(planePoint.y - l->light_source.y) * (planePoint.y - l->light_source.y);
							if (d < l->light_radius * l->light_radius)
							{
								intensity = l->light_intensity * (1.0f - d / (l->light_radius * l->light_radius));
								Color = { (1.0f - intensity) * Color.r + (intensity * l->light_color.r),
								(1.0f - intensity) * Color.g + (intensity * l->light_color.g), (1.0f - intensity) * Color.b + (intensity * l->light_color.b) };

								Shade = { (1.0f - intensity) * Shade.r + (intensity * l->light_color.r),
								(1.0f - intensity) * Shade.g + (intensity * l->light_color.g), (1.0f - intensity) * Shade.b + (intensity * l->light_color.b) };
							}
						}
					}



					if (m_UseIntensity)
						Color = Color * Shade;

					if (m_Fog)
					{
						Fog = Fog / 20.0f;
						Color = { (1.0f - Fog.r) * Color.r + (Fog.r),
							(1.0f - Fog.g) * Color.g + (Fog.g), (1.0f - Fog.b) * Color.b + (Fog.b) };
					}
					if (m_LSD)
					{
						Color = Color * vec3(100.0f, 100.0f, 100.0f);
						Renderer::setPixel_n({ (float)x, (float)y }, Color);
					}
					else Renderer::setPixel({ (float)x, (float)y }, Color);
				}
			}
			thread->s_isRunning = false;
		}
		thread->s_Condition.notify_one();
		if (thread->s_Quit)
			break;
	}
}
