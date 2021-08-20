#include "Core/RaycastPCH.h"

#include "RaycastEngine.h"

class Odium : public Application
{
public:
	Odium(const wchar_t* title) : Application(title), m_Emmiter(200) {}

	virtual void onCreate() override
	{
		m_CeilTex = std::make_shared<Sprite>("Resources/Floor.spr");
		Map::Get()->loadMap("Resources/Map2.rmap");
		//WorldRenderer::setCeilTexture(m_CeilTex);
		WorldRenderer::setCeilGradient({ 0.5, 0.8, 1.0f }, { 1.0f, 1.0f, 1.0f }, 120.0f);
		//WorldRenderer::setCeilColor({ 1.0f, 1.0f, 1.0f });
		WorldRenderer::setIntensity(0.4f);

		ParticleProps Snow;
		Snow.m_Scale = { 1.0f, 1.0f };
		Snow.m_LifeTime = 5.0f;
		Snow.m_Position = { 160.0f, 250.0f };
		Snow.m_Speed = 110.0f;
		Snow.m_Velocity = { 0.0f, -1.0f };
		Snow.m_VelocityVariation = { 0.5f, 0.5f };

		m_Emmiter.setEmissionRate(1);
		m_Emmiter.setEmissionTime(0.07f);

		m_Emmiter.setColor({ 1.0f * 0.8f, 1.0f * 0.8f, 1.0f * 0.8f });

		ParticleManager::addParticleType("Snow", Snow);
	}

	virtual void onUpdate(float dt) override
	{
		WorldRenderer::Render(m_Buffer, m_Camera);

		ParticleManager::getParticle("Snow").m_Position.x = Random::Float() * m_Buffer->getWidth();
		float sc = Random::Float();
		ParticleManager::getParticle("Snow").m_Scale.x = sc;
		ParticleManager::getParticle("Snow").m_Scale.y = sc;

		m_Emmiter.Emit(ParticleManager::getParticle("Snow"), dt);
		m_Emmiter.Update(dt);
		m_Emmiter.Render();
	}

private:
	std::shared_ptr<Sprite> m_CeilTex;
	ParticleEmmiter m_Emmiter;
};

int main()
{
	Application* OdiumAscensiunea = new Odium(L"Odium Ascensiunea");
	OdiumAscensiunea->setCamera(1, 1, 60.0f);

	OdiumAscensiunea->Run();

	delete OdiumAscensiunea;
	return 0;
}