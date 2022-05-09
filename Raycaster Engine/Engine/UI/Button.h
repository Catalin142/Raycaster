#pragma once
#include "InteractableUI.h"

class Button : public InteractableUI
{
	friend class DropdownMenu;

	virtual UIInterationType getInteractionType() override { return Mouse; }

public:
	Button(const std::shared_ptr<Sprite>& spr, float width, float height);
	Button(const std::string& filepath, float width, float height);
	Button(const vec3& color, float width, float height);
};