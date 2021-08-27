#pragma once
#include "Maths.h"

vec2 getMousePosition();

void setMousePosition(int x, int y);
void setCursorVisibility(bool cursor);

void pinMouse();

vec2 WindowToBufferCoordonates(const vec2& vec);

#define VK_MOUSE_LEFT 1
#define VK_MOUSE_RIGHT 2
#define VK_MOUSE_MIDDLE 3
