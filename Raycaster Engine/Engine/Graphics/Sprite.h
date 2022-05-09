#pragma once
#include <string>

#include "Utils/Maths.h"

class Sprite
{
	friend class Renderer;
	friend class TextBox;
	friend class InteractableUI;

public:
	Sprite() = default;
	Sprite(const std::string& filepath);
	~Sprite() = default;

	bool loadSprite(const std::string& filepath);
	const vec3& getPixelColor(float x, float y) const;

	float getAspectRatio() { return (float)m_Width / (float)m_Height; }

private:
	vec3* m_Buffer = nullptr;

	int m_Width;
	int m_Height;

	std::string m_Filepath;
};