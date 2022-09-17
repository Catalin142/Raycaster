#pragma once
#include "RaycastEngine.h"

class RaycasterDemo : public Layer
{
public:
	RaycasterDemo() : Layer() { }

	virtual void onAttach() override;
	virtual void onUpdate(float dt) override;

private:
	std::shared_ptr<Scene> m_Scene;

	std::shared_ptr<TextBox> m_TextBox;
	std::shared_ptr<Sprite> m_Frame;
	std::shared_ptr<Sprite> m_Sword;

	std::shared_ptr<Camera> m_Camera;
};