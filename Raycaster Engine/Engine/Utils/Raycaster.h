#pragma once
#include "Maths.h"
#include "Renderer/Camera.h"
#include "Map.h"
#include <cmath>
#include "Tools/Benchmark.h"

struct RaycastResult
{
	float Length;
	float Depth;

	float HitPosition;
	int Side;

	char Symbol;
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

	RaycastResult res;

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

		for (const auto& elem : Map::Get()->getElements())
		{
			if (elem.isWall == true)
				if (Map::Get()->getBuffer()[(int)lineMapPos.y * Map::Get()->getWidth() + (int)lineMapPos.x] == elem.Symbol)
				{
					collide = 1;
					res.Symbol = elem.Symbol;
				}
		}

		if (length > 200.0f)
			break;
	}
	
	vec2 linePosition = cam->m_Position + rayDir * length;

	if (Side == 1)
		res.HitPosition = linePosition.y - (int)linePosition.y;
	else
		res.HitPosition = linePosition.x - (int)linePosition.x;
	
	res.Depth = length;

	length *= cos(angle - cam->m_CameraAngle);
	res.Length = length;
	res.Side = Side;

	return res;
}