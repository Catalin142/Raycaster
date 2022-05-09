#include "Raycaster.h"

void RaycasterGame::onAttach()
{
	Subscribe<MousePressedEvent>();
	Subscribe<KeyDownEvent>();

	m_CeilTex = std::make_shared<Sprite>("Resources/Floor.spr");

	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");
	m_TextBox = std::make_shared<TextBox>(m_Frame, 250.0f, 30.0f);
	m_TextBox->setPosition(Center | Bottom);
	m_TextBox->setOffset(30, 10);
	m_TextBox->setText("Cata e cel mai cool xd", Center, { 1.0f, 1.0f, 1.0f });
	
	m_Scene = std::make_shared<Scene>();
	m_Snowman = std::make_shared<Entity>("Resources/Snowman.spr");
	m_Snowman->setPosition(1.5f, 1.5f);

	m_Scene->addEntity(m_Snowman);

	Map::Get()->loadMap("Resources/Map2.rmap");

	WorldRenderer::setCeilGradient({ 0.5f, 0.8f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 100.0f);
	WorldRenderer::setIntensity(0.08f);

	ParticleProps Snow;
	Snow.m_Scale = { 1.0f, 1.0f };
	Snow.m_Radius = 1.0f;
	Snow.m_Position = { 160.0f, 200.0f };
	Snow.m_Speed = 110.0f;
	Snow.m_Velocity = { 0.0f, -1.0f };
	Snow.m_VelocityVariation = { 0.0f, 0.0f };
	Snow.m_LifeTime = 2.0f;

	Snow.m_BegColor = { 1.0f, 1.0f, 1.0f };
	Snow.m_EndColor = { 1.0f, 1.0f, 1.0f };

	m_Emmiter.setEmissionRate(1);
	m_Emmiter.setEmissionTime(0.07f);
	m_Emmiter.setType(ParticleType::CIRCLE);

	ParticleManager::addParticleType("Snow", Snow);

	m_Camera = std::make_shared<Camera>(1.5f, 1.5f, 60.0f, 3.0f);
	UiManager->addButton("buton1", std::make_shared<Button>(vec3(1.0f, 1.0f, 1.0f), 100.0f, 100.0f));
	(*UiManager)["buton1"]->setPosition(Center);
	UiManager->addButton("buton2", std::make_shared<Button>(vec3(0.0f, 1.0f, 1.0f), 50.0f, 50.0f));
	(*UiManager)["buton2"]->setPosition(Center);
}

void RaycasterGame::onUpdate(float dt)
{
	Renderer::beginScene(m_Camera);

	auto m_Buffer = getBuffer();
	m_Camera->onUpdate(dt);
	
	Renderer::Clear(0.0f, 0.0f, 0.0f);
	
	WorldRenderer::Render(m_Buffer, m_Camera);
	
	Renderer::renderScene(m_Scene);
	
	ParticleManager::getParticle("Snow").m_Position.x = Random::Float() * m_Buffer->getWidth();
	m_TextBox->Render();
	
	m_Emmiter.Emit(ParticleManager::getParticle("Snow"), dt);
	m_Emmiter.Update(dt);
	m_Emmiter.Render();
}
