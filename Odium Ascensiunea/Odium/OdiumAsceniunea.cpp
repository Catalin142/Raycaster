#include "Core/RaycastPCH.h"

#include "OdiumAsceniunea.h"

void OdiumAsceniunea::onAttach()
{
	m_CeilTex = std::make_shared<Sprite>("Resources/Floor.spr");

	m_Scene = std::make_shared<Scene>();
	m_Snowman = std::make_shared<Entity>("Resources/Snowman.spr");
	m_Snowman->setPosition(1.5f, 1.5f);

	m_Scene->addEntity(m_Snowman);

	Map::Get()->loadMap("Resources/Map2.rmap");

	WorldRenderer::setCeilGradient({ 0.5f, 0.8f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 120.0f);
	//WorldRenderer::setCeilTexture(m_Enemy);
	WorldRenderer::setIntensity(0.6f);

	ParticleProps Snow;
	Snow.m_Scale = { 1.0f, 1.0f };
	Snow.m_Radius = 5.0f;
	Snow.m_Position = { 160.0f, 200.0f };
	Snow.m_Speed = 110.0f;
	Snow.m_Velocity = { 0.0f, -1.0f };
	Snow.m_VelocityVariation = { 0.0f, 0.0f };
	Snow.m_LifeTime = 2.0f;

	Snow.m_BegColor = { 1.0f, 1.0f, 1.0f };
	Snow.m_EndColor = { 1.0f, 1.0f, 1.0f };

	m_Emmiter.setEmissionRate(1);
	m_Emmiter.setEmissionTime(0.07f);
	m_Emmiter.setType(ParticleType::QUAD);

	ParticleManager::addParticleType("Snow", Snow);
}

void OdiumAsceniunea::onUpdate(float dt)
{
	auto m_Buffer = getBuffer();
	auto m_Camera = getCamera();
	WorldRenderer::Render(m_Buffer, m_Camera);

	Renderer::renderScene(m_Scene);

	ParticleManager::getParticle("Snow").m_Position.x = Random::Float() * m_Buffer->getWidth();
	float sc = Random::Float();
	ParticleManager::getParticle("Snow").m_Scale.x = sc;
	ParticleManager::getParticle("Snow").m_Scale.y = sc;

	m_Emmiter.Emit(ParticleManager::getParticle("Snow"), dt);
	m_Emmiter.Update(dt);
	m_Emmiter.Render();
}