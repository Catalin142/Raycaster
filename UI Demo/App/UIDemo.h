#pragma once
#include "RaycastEngine.h"

class UIDemo : public Layer
{
public:
	UIDemo() : Layer() { }

	virtual void onAttach() override;
	virtual void onUpdate(float dt) override;

private:
	std::shared_ptr<TextBox> m_TextBox;
	std::shared_ptr<Sprite> m_Frame;
};