#include "Core/RaycastPCH.h"

#include "RaycastEngine.h"

class Odium : public Application
{
public:
	Odium(const wchar_t* title) : Application(title) {}

	virtual void onCreate() override
	{
		Map::Get()->loadMap("Resources/Maps.txt", "1");
		m_Wall = std::make_shared<Sprite>("Resources/Wall.spr");
		m_Floor = std::make_shared<Sprite>("Resources/Floor.spr");
	}

	virtual void onUpdate(float dt) override
	{
		vec3 Color;
		vec2 wallSize;
		vec2 wallPos;
		vec3 Shade = White;

		vec3 floorAndCeilShade = White;

		vec2 BufferDim = { (float)m_Buffer->getWidth(), (float)m_Buffer->getHeight() };

		for (int x = 0; x < BufferDim.x; x++)
		{
			float rayAng = (m_Camera->m_CameraAngle - degToRad(m_Camera->m_FOV) / 2.0f) + ((float)x / BufferDim.x) * degToRad(m_Camera->m_FOV);
		
			auto res = castRay(m_Camera, rayAng);
		
			wallSize = { 1.0f, (1600.0f / 900.0f) * BufferDim.y / res.Length };
			wallPos = { (float)x, BufferDim.y / 2.0f - wallSize.y / 2.0f };
		
			Shade = White;
			//if (res.Length > 0.3f)
			//	Shade = White * (0.1f / res.Length);
		
			if (res.Side == 1)
				Shade = Shade / 2.0;
			vec2 rayDir = { cos(rayAng), sin(rayAng) };

			float fishEyeCorrection = 2.0f / std::cos(rayAng - m_Camera->m_CameraAngle);

			for (int y = 0; y < BufferDim.y; y++)
			{
				if (y < wallPos.y)
				{
					//Color = FloorColor / lerp(1.0f, 10.0f, y / 400.0f);

					float Plane = (BufferDim.y / 2.0f) / ((BufferDim.y / 2.0f) - float(y));

					vec2 planePoint = m_Camera->m_Position + rayDir * Plane * fishEyeCorrection;
					//floorAndCeilShade = White * (0.1f / Plane);

					float pixelX = planePoint.x - (int)planePoint.x;
					float pixelY = planePoint.y - (int)planePoint.y;

					Color = createRGB(m_Wall->getPixelColor(pixelX, pixelY)) * floorAndCeilShade;
				}

				else if (y >= wallPos.y && y <= wallPos.y + wallSize.y)
					Color = createRGB(m_Wall->getPixelColor(res.HitPosition, (y - wallPos.y) / (int)(wallSize.y + 1))) * Shade;

				else if (y > wallPos.y + wallSize.y)
				{
					float Plane = (BufferDim.y / 2.0f) / ((BufferDim.y / 2.0f) - float(y));

					vec2 planePoint = m_Camera->m_Position - rayDir * Plane * fishEyeCorrection;
					//floorAndCeilShade = White * (0.1f / (-Plane));

					float pixelX = planePoint.x - (int)planePoint.x;
					float pixelY = planePoint.y - (int)planePoint.y;

					Color = createRGB(m_Wall->getPixelColor(pixelX, pixelY)) * floorAndCeilShade;
				}

				Renderer::setPixel({ (float)x, (float)y }, Color, false);
			}

		}
		Map::Get()->updatePlayerPosition(m_Camera->m_Position);
		Map::Get()->Draw(50.0f, 50.0f, 5.0f, 7.0f);

		//Renderer::renderSprite(m_Wall, { 100, 100 }, { 5, 7 });
	}

private:
	vec3 SunriseColor = { 0.86f, 0.78f, 0.0f };
	vec3 SkyColor = { 0.1f, 0.2f, 0.8f };

	std::shared_ptr<Sprite> m_Wall;
	std::shared_ptr<Sprite> m_Floor;

};

int main()
{
	Application* OdiumAscensiunea = new Odium(L"Odium Ascensiunea");
	OdiumAscensiunea->setCamera(1, 1, 60.0f);

	OdiumAscensiunea->Run();

	delete OdiumAscensiunea;
	return 0;
}