#include "RaycasterDemo.h"

void RaycasterDemo::onAttach()
{
	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");

	m_TextBox = std::make_shared<TextBox>(m_Frame, 160.0f, 20.0f);
	m_TextBox->setPosition(Center | Bottom);
	m_TextBox->setOffset(30, 10);
	m_TextBox->setText("Minotaur Labyrinth", Center, { 1.0f, 1.0f, 1.0f });

	m_Scene = std::make_shared<Scene>();
	m_Scene->loadScene("Resources/dungeon.scene");

	m_Camera = std::make_shared<Camera>(60.0f, 3.0f);
	WorldRenderer::setGlobalIlluminationIntensity(0.9f);

	Input::showCursor(false);
}

void RaycasterDemo::onUpdate(float dt)
{
	Renderer::beginScene(m_Camera);
	m_Camera->onUpdate(dt);
	Input::pinMouse(true);
	
	auto m_Buffer = getBuffer();
	
	Renderer::Clear(0.0f, 0.0f, 0.0f);
	WorldRenderer::Render(m_Buffer, m_Camera);
	Renderer::renderScene(m_Scene);
	m_TextBox->Render();
	UiManager->onRender();
}