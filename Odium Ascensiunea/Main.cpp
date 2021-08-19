#include "Core/RaycastPCH.h"

#include "RaycastEngine.h"

class Odium : public Application
{
public:
	Odium(const wchar_t* title) : Application(title) {}

	virtual void onCreate() override
	{
		Map::Get()->loadMap("Resources/Map2.rmap");
	}

	virtual void onUpdate(float dt) override
	{
		WorldRenderer::Render(m_Buffer, m_Camera);
	}
};

int main()
{
	Application* OdiumAscensiunea = new Odium(L"Odium Ascensiunea");
	OdiumAscensiunea->setCamera(1, 1, 60.0f);

	OdiumAscensiunea->Run();

	delete OdiumAscensiunea;
	return 0;
}