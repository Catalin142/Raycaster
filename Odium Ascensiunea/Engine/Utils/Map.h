#pragma once

#include "Types.h"
#include "Maths.h"

#include <string>
#include "Graphics/Sprite.h"

struct MapElement
{
	bool isWall;
	char Symbol;

	std::shared_ptr<Sprite> Sprite;
};

class Map
{
	friend class WorldRenderer;

public:
	~Map() = default;

	void setMap(const std::string& filepath);

	uint getWidth() { return m_Width; }
	uint getHeight() { return m_Height; }
	char* getBuffer() { return m_Map; }
	void loadMap(const std::string& filepath);

	void Draw(float x, float y, float sizex, float sizey);
	void updatePlayerPosition(const vec2& pos);

	char getSymbol(int x, int y) { return m_Map[y * m_Width + x]; }

	std::vector<MapElement>& getElements() { return m_Elements; }
	std::shared_ptr<Sprite>& getSprite(char symbol);
	std::shared_ptr<Sprite>& getSprite(int x, int y);

	static std::shared_ptr<Map> Get();

private:
	static char m_Map[50 * 50];

	static uint m_Width;
	static uint m_Height;

	static vec2 m_PlayerPos;

	static std::vector<MapElement> m_Elements;
	static std::unordered_map<char, std::shared_ptr<Sprite>> m_SymbolCache;
private:
	Map() = default;

};