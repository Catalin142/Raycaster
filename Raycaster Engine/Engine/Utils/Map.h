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
	Map() = default;
	~Map() = default;

	void setMap(const std::string& filepath);

	uint getWidth() { return m_Width; }
	uint getHeight() { return m_Height; }
	char* getBuffer() { return m_Buffer; }
	void loadMap(const std::string& filepath);

	void Draw(float x, float y, float sizex, float sizey);
	void updatePlayerPosition(const vec2& pos);
	const vec2& getPlayerPosition() const { return m_PlayerPos; }

	char getSymbol(int x, int y) { return m_Buffer[y * m_Width + x]; }

	std::vector<MapElement>& getElements() { return m_Elements; }
	std::shared_ptr<Sprite>& getSprite(char symbol);
	std::shared_ptr<Sprite>& getSprite(int x, int y);

private:
	char m_Buffer[50 * 50];

	uint m_Width;
	uint m_Height;

	vec2 m_PlayerPos;

	std::vector<MapElement> m_Elements;
	std::unordered_map<char, std::shared_ptr<Sprite>> m_SymbolCache;

};