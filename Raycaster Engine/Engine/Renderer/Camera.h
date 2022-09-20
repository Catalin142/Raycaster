#pragma once

#include "Utils/Maths.h"
#include "Utils/Map.h"

class Scene;

class Camera
{
public:
	Camera() = default;
	Camera(float posx, float posy, float fov, float speed = 5.0f);
	Camera(const std::shared_ptr<Scene>& scn, float fov, float speed = 5.0f);
	~Camera() = default;

	bool onUpdate(const std::shared_ptr<Map> map, float dt);
	float m_CameraAngleVelocity;

private:
	vec2 m_Velocity;

	vec2 m_LastMousePosition;

public:
	vec2 m_Position;

	float m_FOV = 45.0f;
	float m_CameraAngle = 0.1f;
	float m_Speed = 5.0f;
	float m_Sprint = 5.0f;
};