#pragma once

#include "Maths.h"

static unsigned long createHex(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

static vec3 createRGB(unsigned long hex)
{
	vec3 Color;
	Color.x = ((hex >> 16) & 0xFF) / 255.0f;
	Color.y = ((hex >> 8) & 0xFF) / 255.0f;
	Color.z = ((hex) & 0xFF) / 255.0f;
	return Color;
}