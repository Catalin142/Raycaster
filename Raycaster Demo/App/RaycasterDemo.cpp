#include "RaycasterDemo.h"

void RaycasterDemo::onAttach()
{
	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");
	m_Sword = std::make_shared<Sprite>("Resources/Sword.spr");

	m_TextBox = std::make_shared<TextBox>(m_Frame, 160.0f, 20.0f);
	m_TextBox->setPosition(Center | Bottom);
	m_TextBox->setOffset(30, 10);
	m_TextBox->setText("Minotaur Labyrinth", Center, { 1.0f, 1.0f, 1.0f });

	m_Scene = std::make_shared<Scene>();
	m_Scene->loadScene("Resources/dungeon.scene");

	m_Camera = std::make_shared<Camera>(60.0f, 3.0f);
	WorldRenderer::setGlobalIlluminationIntensity(0.3f);
	WorldRenderer::setFog(true, 0.4f);
	WorldRenderer::setCamera(m_Camera);

	Input::showCursor(false);
}

void RaycasterDemo::onUpdate(float dt)
{
	Renderer::beginScene(m_Camera);
	m_Camera->onUpdate(dt);
	Input::pinMouse(true);
	
	auto m_Buffer = getBuffer();
	
	Renderer::Clear(0.0f, 0.0f, 0.0f);
	WorldRenderer::Render();
	Renderer::renderScene(m_Scene);
	Renderer::renderSprite(m_Sword, { getBuffer()->getWidth() / 2.0f + 100.0f, 0.0f }, { 5, 10 });
	Map::Get()->Draw(getBuffer()->getWidth() - Map::Get()->getWidth() * 2.5, getBuffer()->getHeight() - Map::Get()->getHeight() * 2.5, 2, 2);
	//m_TextBox->Render();
	UiManager->onRender();
}