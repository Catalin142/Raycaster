#pragma once
#include "InteractableUI.h"
#include "Button.h"
#include "DropdownMenu.h"
#include "InputBox.h"
#include "Events/Event.h"

class UIManager
{
public:
	UIManager() = default;
	~UIManager() = default;

	void addButton(const char* name, const std::shared_ptr<Button>& button);
	void addDropdownMenu(const char* name, const std::shared_ptr<DropdownMenu>& menu);
	void addInputBox(const char* name, const std::shared_ptr<InputBox>& box);

	std::shared_ptr<InteractableUI>& operator[](const char* name);

	bool onEvent(Event& event);
	void onRender();

private:

	struct UIElement
	{
		const char* Name;
		std::shared_ptr<InteractableUI> UI;
	}; // prefer sa fac un struct ca cu unordered map nu pot sa dau reverse inter

	std::vector<UIElement> m_UIElements;
};