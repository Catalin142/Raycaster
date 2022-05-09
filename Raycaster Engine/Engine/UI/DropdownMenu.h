#pragma once
#include "InteractableUI.h"
#include "Button.h"
#include "Utils/Color.h"

class DropdownMenu : public InteractableUI
{
public:
	DropdownMenu(const std::shared_ptr<Sprite>& spr, float width, float height);
	DropdownMenu(const std::string& filepath, float width, float height);
	DropdownMenu(const vec3& color, float width, float height);

	virtual void Render() override;
	void addButton(const std::string& name, std::shared_ptr<Button>& button);

	void useFrame(bool use) { m_useFrame = use; }
	void setFrameColor(const vec3& color) { m_FrameColor = createHex(color); }

	std::shared_ptr<Button>& operator[](const char* name);

	virtual UIInterationType getInteractionType() override { return Mouse; }

private:
	std::unordered_map<std::string, std::shared_ptr<Button>> m_Buttons;

	bool m_isOpened = false;

	bool m_useFrame = false;
	unsigned long m_FrameColor = 0xffffff;
};