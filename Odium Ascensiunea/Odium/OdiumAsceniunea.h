#pragma once
#include "RaycastEngine.h"

class OdiumAsceniunea : public Layer
{
public:
	OdiumAsceniunea() : Layer() { }

	virtual void onAttach() override;
	virtual void onUpdate(float dt) override;

private:
	std::shared_ptr<Sprite> m_CeilTex;
	std::shared_ptr<Entity> m_Snowman;
	std::shared_ptr<Scene> m_Scene;

	ParticleEmmiter m_Emmiter;
};