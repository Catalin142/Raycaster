#pragma once

#include "Utils/Maths.h"

class Camera
{
public:
	Camera(float posx, float posy, float fov, float speed = 5.0f);
	~Camera() = default;

	void onUpdate(float dt);

private:
	vec2 m_Velocity;
	float m_Speed = 5.0f;
	float m_Sprint = 5.0f;

	vec2 m_LastMousePosition;

public:
	vec2 m_Position;

	float m_FOV = 45.0f;
	float m_CameraAngle = 0.1f;
};