#include "Core/RaycastPCH.h"

#include "Camera.h"
#include "Utils/Input.h"
#include "Utils/Map.h"
#include "System/Win32Window.h"
#include "Entity/Scene.h"

Camera::Camera(float posx, float posy, float fov, float speed) : m_Position(posx, posy), m_FOV(fov), m_Speed(speed), m_Sprint(m_Speed + 3.0f), m_LastMousePosition(0.0f, 0.0f),
m_Velocity(0.0f, 0.0f) { }

Camera::Camera(const std::shared_ptr<Scene>& scn, float fov, float speed) :  m_FOV(fov), m_Speed(speed), m_Sprint(m_Speed + 3.0f), m_LastMousePosition(0.0f, 0.0f),
m_Velocity(0.0f, 0.0f) 
{
	m_Position = scn->getMap()->getPlayerPosition();
}

bool Camera::onUpdate(const std::shared_ptr<Map> map, float dt)
{
	m_Velocity = { 0.0f, 0.0f };
	bool moved = false;
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
	m_CameraAngleVelocity = (Window::Get()->getClientRectSize().x / 2.0f - MousePos.x) * 0.0003f;

	m_CameraAngle -= m_CameraAngleVelocity;

	if (!(m_Velocity == vec2(0.0f, 0.0f)))
	{
		moved = true;
		bool camMove = true;
		vec2 CollisionPoint = m_Position + m_Velocity.normalize() * m_Speed * dt * 10.0f;
		for (const auto& sym : map->getElements())
			if (sym.isWall)
				if (map->getBuffer()[(int)CollisionPoint.y * map->getWidth() + (int)CollisionPoint.x] == sym.Symbol)
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

	return moved;
}
