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

	int getWidth() { return m_Width; }
	int getHeight() { return m_Height; }
private:
	vec3* m_Buffer = nullptr;

	int m_Width;
	int m_Height;

	std::string m_Filepath;
};

class SpriteManager
{
public:
	static std::shared_ptr<Sprite>& loadSprite(const std::string& filepath);
private:
	static std::unordered_map<std::string, std::shared_ptr<Sprite>> m_SpriteCache;
};