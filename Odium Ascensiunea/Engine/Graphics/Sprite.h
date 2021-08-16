#pragma once
#include <string>

class Sprite
{
	friend class Renderer;

public:
	Sprite() = default;
	Sprite(const std::string& filepath);
	~Sprite() = default;

	bool loadSprite(const std::string& filepath);
	unsigned long getPixelColor(float x, float y);

private:
	long* m_Buffer = nullptr;

	int m_Width;
	int m_Height;

	std::string m_Filepath;
};