#pragma once
#include "Maths.h"
#include "Renderer/Camera.h"
#include "Map.h"
#include <cmath>

struct RaycastResult
{
	float Length;
	float HitPosition;
	int Side;
};

static RaycastResult castRay(const std::shared_ptr<Camera>& cam, float angle)
{
	vec2 rayDir;
	rayDir.x = cos(angle);
	rayDir.y = sin(angle);

	vec2 raySlope;
	raySlope.x = (float)sqrt((double)1 + (double)(rayDir.y / rayDir.x) * (rayDir.y / rayDir.x));
	raySlope.y = (float)sqrt((double)1 + (double)(rayDir.x / rayDir.y) * (rayDir.x / rayDir.y));

	vec2 blockPos;
	blockPos.x = (float)(int)(cam->m_Position.x);
	blockPos.y = (float)(int)(cam->m_Position.y);

	vec2 startRay;
	vec2 Step = { 0, 0 };
	int Side = 0;

	if (rayDir.x > 0)
	{
		startRay.x = (((blockPos.x + 1) - cam->m_Position.x) * raySlope.x);
		Step.x = 1;
	}
	else
	{
		startRay.x = ((cam->m_Position.x - blockPos.x) * raySlope.x);
		Step.x = -1;
	}

	if (rayDir.y > 0)
	{
		startRay.y = (((blockPos.y + 1) - cam->m_Position.y) * raySlope.y);
		Step.y = 1;
	}
	else
	{
		startRay.y = ((cam->m_Position.y - blockPos.y) * raySlope.y);
		Step.y = -1;
	}

	vec2 lineMapPos = cam->m_Position;

	float length = 0;
	int collide = 0;

	while (collide == 0)
	{
		if (startRay.x < startRay.y)
		{
			length = startRay.x;
			startRay.x += raySlope.x;
			lineMapPos.x += Step.x;
			Side = 1;
		}
		else
		{
			length = startRay.y;
			startRay.y += raySlope.y;
			lineMapPos.y += Step.y;
			Side = 0;
		}

		if (Map::Get()->getBuffer()[(int)lineMapPos.y * Map::Get()->getWidth() + (int)lineMapPos.x] == '#')
			collide = 1;

		if (length > 200.0f)
			break;
	}

	length *= cos(angle - cam->m_CameraAngle);
	
	vec2 linePosition = cam->m_Position + rayDir * length;
	
	RaycastResult res;

	if (Side == 1)
	{
		res.HitPosition = linePosition.y - (int)linePosition.y;
	}
	else
	{
		res.HitPosition = linePosition.x - (int)linePosition.x;
	}

	res.Length = length;
	res.Side = Side;

	return res;
}