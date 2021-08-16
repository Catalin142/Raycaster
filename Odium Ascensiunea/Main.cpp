#include "Core/RaycastPCH.h"

#include "RaycastEngine.h"

class Odium : public Application
{
public:
	Odium(const wchar_t* title) : Application(title) {}

	virtual void onCreate() override
	{
		Map::Get()->loadMap("Resources/Maps.txt", "1");
		m_Sprite = std::make_shared<Sprite>("Resources/Wall.spr");
	}

	virtual void onUpdate(float dt) override
	{
		vec3 Color;
		vec2 wallSize;
		vec2 wallPos;
		vec3 Shade = WallColor;

		for (int x = 0; x < m_Buffer->getWidth(); x++)
		{
			float rayAng = (m_Camera->m_CameraAngle - degToRad(m_Camera->m_FOV) / 2.0f) + ((float)x / m_Buffer->getWidth()) * degToRad(m_Camera->m_FOV);
		
			auto res = castRay(m_Camera, rayAng);
		
			wallSize = { 1.0f, 1.5f * m_Buffer->getHeight() / res.Length };
			wallPos = { (float)x, m_Buffer->getHeight() / 2.0f - wallSize.y / 2.0f };
		
			Shade = WallColor;
			//if (res.Length > 0.5f)
			//	Shade = WallColor / (res.Length / 12.0f);
		
			if (res.Side == 1)
				Shade = Shade / 2.0;
			
			for (int y = 0; y < m_Buffer->getHeight(); y++)
			{
				if (y < wallPos.y)
					Color = FloorColor / lerp(1.0f, 10.0f, y / 400.0f);

				else if (y >= wallPos.y && y <= wallPos.y + wallSize.y)
					Color = createRGB(m_Sprite->getPixelColor(res.HitPosition, (float(y) - wallPos.y) / ((int)wallSize.y + 1))) * Shade;

				else if (y > wallPos.y + wallSize.y)
					Color = lerp(SunriseColor, SkyColor, y / 300.0f);

				Renderer::setPixel({ (float)x, (float)y }, Color, false);
			}
		}

		//Renderer::renderSprite(m_Sprite, { 100, 100 }, { 5, 7 });
	}

private:
	vec3 FloorColor = { 0.1f, 0.7f, 0.3f };
	vec3 SunriseColor = { 0.86f, 0.78f, 0.0f };
	vec3 SkyColor = { 0.1f, 0.2f, 0.8f };
	vec3 WallColor = { 1.0f, 1.0f, 1.0f };

	std::shared_ptr<Sprite> m_Sprite;

};

int main()
{
	Application* OdiumAscensiunea = new Odium(L"Odium Ascensiunea");
	OdiumAscensiunea->setCamera(1, 1, 60.0f);

	OdiumAscensiunea->Run();

	delete OdiumAscensiunea;
	return 0;
}