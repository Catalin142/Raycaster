#include "Core/RaycastPCH.h"

#include "Camera.h"
#include "Utils/Input.h"
#include "Utils/Map.h"
#include "System/Win32Window.h"

Camera::Camera(float posx, float posy, float fov, float speed) : m_Position(posx, posy), m_FOV(fov), m_Speed(speed), m_Sprint(m_Speed + 3.0f), m_LastMousePosition(0.0f, 0.0f),
m_Velocity(0.0f, 0.0f) { }

Camera::Camera(float fov, float speed) :  m_FOV(fov), m_Speed(speed), m_Sprint(m_Speed + 3.0f), m_LastMousePosition(0.0f, 0.0f),
m_Velocity(0.0f, 0.0f) 
{
	m_Position = Map::Get()->getPlayerPosition();
}

void Camera::onUpdate(float dt)
{
	m_Velocity = { 0.0f, 0.0f };
	if (Input::isPressed('W'))
	{
		m_Velocity.x += cos(m_CameraAngle);
		m_Velocity.y += sin(m_CameraAngle);
	}

	if (Input::isPressed('S'))
	{
		m_Velocity.x -= cos(m_CameraAngle);
		m_Velocity.y -= sin(m_CameraAngle);
	}

	if (Input::isPressed('A'))
	{
		m_Velocity.x += sin(m_CameraAngle);
		m_Velocity.y -= cos(m_CameraAngle);
	}

	if (Input::isPressed('D'))
	{
		m_Velocity.x -= sin(m_CameraAngle);
		m_Velocity.y += cos(m_CameraAngle);
	}

	vec2 MousePos = Input::getMousePosition();
	float delta = (Window::Get()->getClientRectSize().x / 2.0f - MousePos.x) * 0.0003f;

	m_CameraAngle -= delta;

	if (!(m_Velocity == vec2(0.0f, 0.0f)))
	{
		bool camMove = true;
		vec2 CollisionPoint = m_Position + m_Velocity.normalize() * m_Speed * dt * 10.0f;
		for (const auto& sym : Map::Get()->getElements())
			if (sym.isWall)
				if (Map::Get()->getBuffer()[(int)CollisionPoint.y * Map::Get()->getWidth() + (int)CollisionPoint.x] == sym.Symbol)
					camMove = false;
		if (camMove)
		{
			if (Input::isPressed(VK_LSHIFT))
			{
				m_Position = m_Position + m_Velocity.normalize() * m_Sprint * dt;

			}
			else m_Position = m_Position + m_Velocity.normalize() * m_Speed * dt;
		}
	}
}
