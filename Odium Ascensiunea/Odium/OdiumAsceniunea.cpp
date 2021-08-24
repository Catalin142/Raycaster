#include "OdiumAsceniunea.h"

void OdiumAsceniunea::onAttach()
{
	m_CeilTex = std::make_shared<Sprite>("Resources/Floor.spr");

	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");
	m_Font = std::make_shared<Font>("Resources/Font1.spr", 6, 7);

	m_TextBox = std::make_shared<TextBox>(m_Frame, m_Font, 250, 50);
	m_TextBox->setPosition({ 35.0f, 25.0f });
	m_TextBox->setText("asudhasdasjkldhasj kdhajksdhajksdhasgdasdasdasdasdasdasdasdsasudhasdasjkldhasjasudhasdasjkldhasj kdhajksdhajksdhasgdasdasdasdasdasdasdasdsasudhasdasjkldhasj", 
		TextCenter, { 1.0f, 1.0f, 1.0f });

	m_Scene = std::make_shared<Scene>();
	m_Snowman = std::make_shared<Entity>("Resources/Snowman.spr");
	m_Snowman->setPosition(1.5f, 1.5f);

	m_Scene->addEntity(m_Snowman);

	Map::Get()->loadMap("Resources/Map2.rmap");

	WorldRenderer::setCeilGradient({ 0.5f, 0.8f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 120.0f);
	//WorldRenderer::setCeilTexture(m_Enemy);
	WorldRenderer::setIntensity(0.8f);

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

	FontManager::addFont("Odium", m_Font);
}

void OdiumAsceniunea::onUpdate(float dt)
{
	/*
	auto m_Buffer = getBuffer();
	auto m_Camera = getCamera();
	WorldRenderer::Render(m_Buffer, m_Camera);

	Renderer::renderScene(m_Scene);

	ParticleManager::getParticle("Snow").m_Position.x = Random::Float() * m_Buffer->getWidth();

	m_Emmiter.Emit(ParticleManager::getParticle("Snow"), dt);
	m_Emmiter.Update(dt);
	m_Emmiter.Render();

	Renderer::drawText("Padurea Spanzuratilor", m_Font, TextCenter | TextTop, 1, { 0.0f, 0.0f, 0.0f });
	*/

	m_TextBox->Render();

}
