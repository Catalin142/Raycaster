#pragma once
#include "RaycastEngine.h"

class RaycasterDemo : public Layer
{
public:
	RaycasterDemo() : Layer(), m_Emmiter(ParticleEmmiter(500)) { }

	virtual void onAttach() override;
	virtual void onUpdate(float dt) override;

private:
	std::shared_ptr<Scene> m_Scene;

	std::shared_ptr<TextBox> m_TextBox;
	std::shared_ptr<Sprite> m_Frame;

	std::shared_ptr<Sprite> m_Lighter;
	float m_GunPosition;
	float m_GunPosition_y = -100.0f;

	Light* m_playerLight;
	ParticleProps m_FireParticle; 
	ParticleEmmiter m_Emmiter;

	float m_Cooldown = 1.0f;

	void addSkeletons();
	bool added = false;
	bool stop = false;

	vec3 m_HandColor = { 1.0f, 1.0f, 1.0f };
};