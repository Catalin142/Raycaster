#include "RaycasterDemo.h"

void RaycasterDemo::onAttach()
{
	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");
	m_Lighter = std::make_shared<Sprite>("Resources/Lighter.spr");

	m_TextBox = std::make_shared<TextBox>(m_Frame, 160.0f, 20.0f);
	m_TextBox->setPosition(Center | Bottom);
	m_TextBox->setOffset(30, 10);
	m_TextBox->setText("Minotaur Labyrinth", Center, { 1.0f, 1.0f, 1.0f });

	m_Scene = std::make_shared<Scene>();
	m_Scene->loadScene("Resources/dungeon.scene");

	WorldRenderer::setGlobalIlluminationIntensity(0.4f);
	//WorldRenderer::setCeilGradient({ 84.0f / 255.0f, 107.0f / 255.0f, 171.0f / 255.0f }, { 19.0f / 255.0f, 24.0f / 255.0f, 98.0f / 255.0f }, 1.0f);
	//WorldRenderer::setFog(true, 0.4f);
	m_GunPosition = -10.0f;
	Input::showCursor(false);

	m_Scene->addLight(new Light({ -100.0f, -100.0f },
		{ 0.995f, 0.611f, 0.164f }, 3.5f, 0.4f));
	m_playerLight = m_Scene->getLastLight();
	m_Scene->setCameraProps(60.0f, 4.0f);

	m_FireParticle.m_BegColor = { 251.0f / 255.0f, 183.0f / 255.0f, 65.0f / 255.0f };
	m_FireParticle.m_EndColor = { 128.0f / 255.0f, 9.0f / 255.0f, 9.0f / 255.0f };
	m_FireParticle.m_LifeTime = 0.3f;
	m_FireParticle.m_Scale = { 2.0f, 2.0f };
	m_FireParticle.m_Speed = 60.0f;
	m_FireParticle.m_Velocity = { 0.0f, 0.6f };
	m_FireParticle.m_VelocityVariation = { 0.3f, 0.2f };
}

void RaycasterDemo::onUpdate(float dt)
{
	Renderer::beginScene(m_Scene->getCamera());
	if (m_Scene->Update(dt))
		m_GunPosition += 10.0f * dt;

	Input::pinMouse(true);
	auto m_Buffer = getBuffer();

	Renderer::Clear(0.0f, 0.0f, 0.0f);
	WorldRenderer::Render(m_Scene);
	Renderer::renderScene(m_Scene);

	if (Input::isPressed('R') && WorldRenderer::getGlobalIlluminationIntensity() >= 0.0f)
		WorldRenderer::setGlobalIlluminationIntensity(WorldRenderer::getGlobalIlluminationIntensity() - dt * 0.5f);

	m_HandColor = { m_FireParticle.m_LifeTime , m_FireParticle.m_LifeTime , m_FireParticle.m_LifeTime };
	if (WorldRenderer::getGlobalIlluminationIntensity() <= 0.0f)
	{
		Renderer::renderSprite(m_Lighter, { (getBuffer()->getWidth() / 2.0f + 20.0f) + cos(m_GunPosition) * 10.0f, 
			lerp(cos(m_GunPosition) * 10.0f - 9.0f, m_GunPosition_y, m_Cooldown) },
			{7, 7}, m_HandColor);

		if (m_Cooldown <= 0.0f)
		{
			addSkeletons();
			m_playerLight->light_source = m_Scene->getMap()->getPlayerPosition() - (Random::Float() * 2.0f - 1.0f) * 0.1f;
			m_FireParticle.m_Position = { (getBuffer()->getWidth() / 2.0f + 40.0f) + cos(m_GunPosition) * 10.0f + 15.0f + Random::Float() * 7,
				cos(m_GunPosition) * 10.0f + m_Lighter->getHeight() * 4.0f + 37.0f };
			m_FireParticle.m_Velocity.x = m_Scene->getCamera()->m_CameraAngleVelocity * 60.0f;

			m_Emmiter.Update(dt);
			m_Emmiter.Emit(m_FireParticle, dt);
			m_Emmiter.Render();
		}
		else m_Cooldown -= dt;
	}

	if (Input::isPressed('T'))
		stop = true;
	if (stop)
	{
		m_FireParticle.m_LifeTime -= (dt * 0.2f);
		if (m_FireParticle.m_LifeTime >= 0.0f)
			m_playerLight->light_radius -= (dt);

		else {
			m_FireParticle.m_LifeTime = 0.0f;
			m_playerLight->light_source = { -100.0f, -100.0f };
		}
	}
	//m_TextBox->Render();
	UiManager->onRender();
}

void RaycasterDemo::addSkeletons()
{
	if (added == false)
	{
		m_Scene->createEntity(1.5f, 1.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(15.5f, 5.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(7.5f, 2.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(9.5f, 2.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(8.5f, 8.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(13.5f, 9.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(2.5f, 17.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(4.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(6.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(7.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(8.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(9.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(10.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(11.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(13.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(14.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(15.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(16.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(17.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		m_Scene->createEntity(18.5f, 18.5f, 0.2f, 0.8f, "Resources/dungeon/skeleton.spr");
		added = true;
	}
}