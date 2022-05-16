#include "UIDemo.h"

void UIDemo::onAttach()
{
	Subscribe<MousePressedEvent>();

	m_Frame = std::make_shared<Sprite>("Resources/Frame.spr");
	m_TextBox = std::make_shared<TextBox>(m_Frame, 120.0f, 20.0f);
	m_TextBox->setMargin({ 0.0f, 30.0f });
	m_TextBox->setPosition(Center | Bottom);
	m_TextBox->setOffset(10, 10);
	m_TextBox->setText("This is a text box", Center, { 1.0f, 1.0f, 1.0f });

	UiManager->addButton("Button1", std::make_shared<Button>(createRGB(0x2E00FF), 170.0f, 15.0f));
	(*UiManager)["Button1"]->setPosition({ 10.0f, 150.0f });
	(*UiManager)["Button1"]->setText("Button1: random background color", Center, {1.0f, 1.0f, 1.0f});
	(*UiManager)["Button1"]->setCallback([] () -> void {Renderer::setClearColor(Random::Float(), Random::Float(), Random::Float()); });

	std::shared_ptr<DropdownMenu> menu = std::make_shared<DropdownMenu>(createRGB(0x2E00FF), 130.0f, 15.0f);
	menu->setPosition({ 280.0f, 150.0f });
	menu->setText("Select background color", Center, { 1.0f, 1.0f, 1.0f });

	menu->addButton("Black", std::make_shared<Button>(createRGB(0x2E00FF), 130.0f, 15.0f));
	(*menu)["Black"]->setCallback([]()->void {Renderer::setClearColor(0.0f, 0.0f, 0.0f); });

	menu->addButton("White", std::make_shared<Button>(createRGB(0x2E00FF), 130.0f, 15.0f));
	(*menu)["White"]->setCallback([]()->void {Renderer::setClearColor(1.0f, 1.0f, 1.0f); });

	menu->addButton("Blue", std::make_shared<Button>(createRGB(0x2E00FF), 130.0f, 15.0f));
	(*menu)["Blue"]->setCallback([]()->void {Renderer::setClearColor(0.0f, 0.0f, 1.0f); });

	menu->addButton("Red", std::make_shared<Button>(createRGB(0x2E00FF), 130.0f, 15.0f));
	(*menu)["Red"]->setCallback([]()->void {Renderer::setClearColor(1.0f, 0.0f, 0.0f); });

	menu->addButton("Green", std::make_shared<Button>(createRGB(0x2E00FF), 130.0f, 15.0f));
	(*menu)["Green"]->setCallback([]()->void {Renderer::setClearColor(0.0f, 1.0f, 0.0f); });

	UiManager->addDropdownMenu("Background_dropdown", menu);
}

void UIDemo::onUpdate(float dt)
{
	Renderer::Clear();

	m_TextBox->Render();
	UiManager->onRender();
}