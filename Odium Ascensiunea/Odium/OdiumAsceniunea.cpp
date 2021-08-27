#include "OdiumAsceniunea.h"

void OdiumAsceniunea::onAttach()
{
	Subscribe<MousePressedEvent>();

	m_CeilTex = std::make_shared<Sprite>("Resources/Floor.spr");

	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");
	m_Font = std::make_shared<Font>("Resources/Font.spr", 6, 7);

	m_TextBox = std::make_shared<TextBox>(m_Frame, m_Font, 250.0f, 30.0f);
	m_TextBox->setPosition(Center | Bottom);
	m_TextBox->setOffset(5, 5);
	m_TextBox->setText("The quick brown fox jumps over the lazy dog", 
		Center, { 1.0f, 1.0f, 1.0f });
	
	m_Scene = std::make_shared<Scene>();
	m_Snowman = std::make_shared<Entity>("Resources/Snowman.spr");
	m_Snowman->setPosition(1.5f, 1.5f);

	m_Scene->addEntity(m_Snowman);

	Map::Get()->loadMap("Resources/Map2.rmap");

	WorldRenderer::setCeilGradient({ 0.5f, 0.8f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 120.0f);
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

	m_Button = std::make_shared<Button>(vec3(0.2f, 0.5f, 0.9f), m_Font, 30.0f, 7.0f);
	m_Button->setPosition({ 100.0f, 100.0f });
	m_Button->setText("Cata", Center, { 0.0f, 0.0f, 0.0f });

	m_Camera = std::make_shared<Camera>(1.5f, 1.5f, 60.0f, 3.0f);
}

void OdiumAsceniunea::onUpdate(float dt)
{
	auto m_Buffer = getBuffer();
	/*

	m_Camera->onUpdate(dt);
	
	WorldRenderer::Render(m_Buffer, m_Camera);
	*/
	Renderer::Clear(0.0f, 0.0f, 0.0f);

	Renderer::beginScene(m_Camera);

	Renderer::renderScene(m_Scene);

	ParticleManager::getParticle("Snow").m_Position.x = Random::Float() * m_Buffer->getWidth();
	m_TextBox->Render();

	m_Emmiter.Emit(ParticleManager::getParticle("Snow"), dt);
	m_Emmiter.Update(dt);
	m_Emmiter.Render();
	
	Renderer::drawText("Padurea Spanzuratilor", m_Font, Center | Top, 1, { 0.0f, 0.0f, 0.0f });
	m_Button->Render();

	Renderer::endScene();
	
}

bool OdiumAsceniunea::onEvent(Event& event)
{
	if (event.getType() == EventType::MousePressed)
	{
		auto ev = static_cast<MousePressedEvent&>(event);
		if (ev.getMouseCode() == VK_MOUSE_LEFT)
		{
			vec2 mousePos = WindowToBufferCoordonates({ (float)ev.getX(), (float)ev.getY() });
			if (m_Button->onMousePressed(mousePos.x, mousePos.y));
				return true;
		}
	}

	return false;
}
