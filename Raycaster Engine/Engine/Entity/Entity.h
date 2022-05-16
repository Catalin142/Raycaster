#pragma once
#include <memory>

#include "Graphics/Sprite.h"
#include "Utils/Maths.h"
#include "Renderer/Camera.h"

class Entity
{
	friend class Scene;
	friend class Renderer;

public:
	Entity() = default;
	Entity(const std::string& filepath);
	Entity(const std::shared_ptr<Sprite>& spr);

	virtual ~Entity() = default;

	virtual void onCreate() { }
	virtual void onUpdate(float dt) { }

	void onDraw(const std::shared_ptr<Camera>& cam);
	void setSprite(const std::string& filepath);

	void setWidth(float width) { m_Width = width; }
	void setHeight(float height) { m_Height = height; }

	void setPosition(float x, float y) { m_Position = { x, y }; }
	void setObjectIllumination(float ill) { m_ObjectIntensity = ill; m_UseObjIntensity = true; }
	void illuminateObject(bool use) { m_UseObjIntensity = use; }

	void applyGlobalIllumination(bool a) { m_ApplyGlobalIllumination = a; }

protected:
	float m_Width = 1.0f;
	float m_Height = 1.0f;

	std::shared_ptr<Sprite> m_Sprite = nullptr;
	vec2 m_Position = { 0.0f, 0.0f };

	bool m_Initialized = false;
	bool m_Visible = true;

	bool m_ApplyGlobalIllumination = true;

	bool m_UseObjIntensity = false;
	float m_ObjectIntensity = 1.0f;
};