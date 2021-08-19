#pragma once

#include "Maths.h"

static unsigned long createHex(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

static vec3 createRGB(unsigned long hex)
{
	float r = ((hex >> 16) & 0xFF);
	float g = ((hex >> 8) & 0xFF);
	float b = ((hex) & 0xFF);
	return vec3(r, g, b) / 255.0f;
}

#define White {1.0f, 1.0f, 1.0f}
#define Black (0.0f, 0.0f, 0.0f)