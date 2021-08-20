#pragma once
#include <string>

#include "Utils/Maths.h"

class Sprite
{
	friend class Renderer;

public:
	Sprite() = default;
	Sprite(const std::string& filepath);
	~Sprite() = default;

	bool loadSprite(const std::string& filepath);
	vec3& getPixelColor(float x, float y);

private:
	vec3* m_Buffer = nullptr;

	int m_Width;
	int m_Height;

	std::string m_Filepath;
};