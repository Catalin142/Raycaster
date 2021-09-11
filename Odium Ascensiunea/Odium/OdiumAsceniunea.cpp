#include "OdiumAsceniunea.h"

void OdiumAsceniunea::onAttach()
{
	Subscribe<MousePressedEvent>();
	Subscribe<KeyDownEvent>();

	m_CeilTex = std::make_shared<Sprite>("Resources/Floor.spr");

	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");

	m_InputBox = std::make_shared<InputBox>(vec3(0.5f, 0.8f, 1.0f), 130.0f, 10.0f);
	m_InputBox->setPosition(Center);
	m_InputBox->setTextAlignment(Center);
	m_InputBox->setTextColor({ 0.5f, 0.2f, 1.0f });

	m_TextBox = std::make_shared<TextBox>(m_Frame, 250.0f, 30.0f);
	m_TextBox->setPosition(Center | Bottom);
	m_TextBox->setOffset(30, 10);
	m_TextBox->setText("the quick fox jumped over the lazy dog", 
		Center, { 1.0f, 1.0f, 1.0f });
	
	m_Scene = std::make_shared<Scene>();
	m_Snowman = std::make_shared<Entity>("Resources/Snowman.spr");
	m_Snowman->setPosition(1.5f, 1.5f);

	m_Scene->addEntity(m_Snowman);

	Map::Get()->loadMap("Resources/Map2.rmap");

	WorldRenderer::setCeilGradient({ 0.5f, 0.8f, 1.0f }, { 1.0f, 1.0f, 1.0f }, 100.0f);
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

	m_Button = std::make_shared<Button>(m_Frame, 30.0f, 7.0f);
	m_Button->setPosition({ 100.0f, 100.0f });
	m_Button->setText("Cata", Center, { 1.0f, 1.0f, 1.0f });

	m_DropdownMenu = std::make_shared<DropdownMenu>(m_Frame, 25.0f, 10.0f);
	m_DropdownMenu->setPosition({ 100.0f, 100.0f });
	m_DropdownMenu->setText("Drop", Center, { 1.0f, 0.0f, 0.0f });
	m_DropdownMenu->addButton("cata", std::make_shared<Button>(vec3(0.8f, 0.1f, 0.6f), 10.0f, 10.0f));
	(*m_DropdownMenu)["cata"]->setText("cata", Center, { 0.0f, 0.0f, 0.0f });

	m_Camera = std::make_shared<Camera>(1.5f, 1.5f, 60.0f, 3.0f);
}

void OdiumAsceniunea::onUpdate(float dt)
{
	auto m_Buffer = getBuffer();
	//m_Camera->onUpdate(dt);
	
	Renderer::Clear(0.0f, 0.0f, 0.0f);
	
	//WorldRenderer::Render(m_Buffer, m_Camera);
	
	Renderer::beginScene(m_Camera);
	Renderer::renderScene(m_Scene);
	
	ParticleManager::getParticle("Snow").m_Position.x = Random::Float() * m_Buffer->getWidth();
	m_TextBox->Render();
	
	m_Emmiter.Emit(ParticleManager::getParticle("Snow"), dt);
	m_Emmiter.Update(dt);
	m_Emmiter.Render();
	
	m_DropdownMenu->Render();

	//m_Button->Render();
	//m_InputBox->Render();
	
	Renderer::endScene();
}

bool OdiumAsceniunea::onEvent(Event& event)
{
	if (event.getType() == EventType::MousePressed)
	{
		auto ev = static_cast<MousePressedEvent&>(event);
		if (ev.getMouseCode() == VK_MOUSE_LEFT)
		{
			vec2 mousePos = Input::WindowToBufferCoordonates({ (float)ev.getX(), (float)ev.getY() });
			if (m_DropdownMenu->onMousePressed(mousePos.x, mousePos.y))
				return true;
			else if (m_InputBox->onMousePressed(mousePos.x, mousePos.y))
				return true;
		}
	}

	if (event.getType() == EventType::KeyDown)
	{
		auto ev = static_cast<KeyDownEvent&>(event);
		m_InputBox->onKeyDown(ev.getKeyCode());
	}

	return false;
}
