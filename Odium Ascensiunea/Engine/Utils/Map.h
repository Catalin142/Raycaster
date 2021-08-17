#pragma once

#include "Types.h"
#include "Maths.h"

#include <string>
class Map
{
public:
	~Map() = default;

	void setMap(const std::string& filepath, const std::string& mapname);

	uint getWidth() { return m_Width; }
	uint getHeight() { return m_Height; }
	char* getBuffer() { return m_Map; }
	void loadMap(const std::string& filepath, const std::string& mapname);

	void Draw(float x, float y, float sizex, float sizey);
	void updatePlayerPosition(const vec2& pos);

	static std::shared_ptr<Map> Get();

private:
	static char m_Map[50 * 50];

	static uint m_Width;
	static uint m_Height;

	static vec2 m_PlayerPos;
private:
	Map() = default;

};