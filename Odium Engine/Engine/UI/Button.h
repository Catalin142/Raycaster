#pragma once
#include "InteractableUI.h"

class Button : public InteractableUI
{
public:
	Button(const std::shared_ptr<Sprite>& spr, const std::shared_ptr<Font>& font, float width, float height);
	Button(const std::string& filepath, const std::shared_ptr<Font>& font, float width, float height);
	Button(const vec3& color, const std::shared_ptr<Font>& font, float width, float height);

	virtual bool onMousePressed(int mousex, int mousey) override;
	virtual bool isHovered() override;
};