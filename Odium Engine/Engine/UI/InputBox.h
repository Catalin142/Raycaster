#pragma once
#include "InteractableUI.h"

class InputBox : public InteractableUI
{
public:
	InputBox(const std::shared_ptr<Sprite>& spr, float width, float height);
	InputBox(const std::string& filepath, float width, float height);
	InputBox(const vec3& color, float width, float height);

	virtual bool onMousePressed(int mousex, int mousey) override;

	void onKeyDown(int code);

private:
	bool m_WaitForInput = false;
	std::string m_Buffer = "";

	vec2 m_CursorPosition = { 0.0f, 0.0f };
};